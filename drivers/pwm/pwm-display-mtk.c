#include <common.h>
#include <clk.h>
#include <dm.h>
#include <display_pwm.h>
#include <asm/io.h>

#define DISPLAY_PWM_EN_OFF     0x0
#define DISPLAY_PWM_COMMIT_OFF 0x8
#define DISPLAY_PWM_CON_1_OFF  0x14

struct mtk_display_pwm_priv {
	void __iomem *base;
    struct clk clk;
    int pwm_inited;
    uint8_t pwm_current;
};

static int mtk_display_pwm_is_enabled(struct udevice *dev){
    struct mtk_display_pwm_priv *priv = dev_get_priv(dev);
    return readl(priv->base + DISPLAY_PWM_EN_OFF) & 1;
}

static void mtk_display_pwm_set_enabled(struct udevice *dev, int enable){
    struct mtk_display_pwm_priv *priv = dev_get_priv(dev);
    if(enable){
        if(!mtk_display_pwm_is_enabled(dev))
            writel(priv->base + DISPLAY_PWM_EN_OFF, 0);
    } else
        writel(priv->base + DISPLAY_PWM_EN_OFF, 0);
}

static void mtk_display_pwm_init(struct udevice *dev){
    struct mtk_display_pwm_priv *priv = dev_get_priv(dev);
    if(priv->pwm_inited) return;
    writel(priv->base + DISPLAY_PWM_CON_1_OFF, 1023);
    priv->pwm_inited = 1;
}

int mtk_display_pwm_set_backlight(struct udevice *dev, uint8_t level){
    struct mtk_display_pwm_priv *priv = dev_get_priv(dev);
    // 255 -> 1022
    if(priv->pwm_current == level)
        return 0;
    int level_pwm = 0;
    if(level>=0 && level <= 255)
        level_pwm = (level << 2)+2;

    clk_enable(&priv->clk);
    if(level == 0){
        mtk_display_pwm_set_enabled(dev, 0);
        goto end;
    } else
        mtk_display_pwm_set_enabled(dev, 1);

    mtk_display_pwm_init(dev);

    writel(priv->base + DISPLAY_PWM_COMMIT_OFF, 0);
    writel(priv->base + DISPLAY_PWM_CON_1_OFF, (level_pwm << 16) | 0x3ff);
    writel(priv->base + DISPLAY_PWM_COMMIT_OFF, 1);
    writel(priv->base + DISPLAY_PWM_COMMIT_OFF, 0);

end:
    priv->pwm_current = level;
    return 0;
}

static int mtk_display_pwm_probe(struct udevice *dev)
{
    struct mtk_display_pwm_priv *priv = dev_get_priv(dev);
    priv->base = dev_read_addr_ptr(dev);
    if (!priv->base)
        return -EINVAL;
    int ret = clk_get_by_index(dev, 1, &priv->clk);
    if(ret < 0)
        return ret;
    priv->pwm_current = 0;
    // enable display pwm by default
    mtk_display_pwm_set_backlight(dev, 255);
    return 0;
}

static const struct display_pwm_ops mtk_display_pwm_ops = {
    .set_backlight = mtk_display_pwm_set_backlight
};

static const struct udevice_id mtk_display_pwm_ids[] = {
	{ .compatible = "mediatek,display-pwm" },
	{ }
};

U_BOOT_DRIVER(mtk_display_pwm) = {
	.name = "mtk_display_pwm",
	.id = UCLASS_DISPLAY_PWM,
	.of_match = mtk_display_pwm_ids,
	.ops = &mtk_display_pwm_ops,
	.probe = mtk_display_pwm_probe,
    .priv_auto	= sizeof(struct mtk_display_pwm_priv),
};

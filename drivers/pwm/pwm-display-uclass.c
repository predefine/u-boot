// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2016 Google, Inc
 * Written by Simon Glass <sjg@chromium.org>
 */

#define LOG_CATEGORY UCLASS_DISPLAY_PWM

#include <common.h>
#include <dm.h>
#include <display_pwm.h>

int display_pwm_set_backlight(struct udevice *dev, uint8_t level){
	struct display_pwm_ops *ops = display_pwm_get_ops(dev);

	if (!ops->set_backlight)
		return -ENOSYS;

	return ops->set_backlight(dev, level);
}

int initr_display_pwm(void)
{
	struct udevice *dev;
	struct uclass *uc;
	int ret;

	ret = uclass_get(UCLASS_DISPLAY_PWM, &uc);
	if (ret) {
		log_debug("Error getting UCLASS_DISPLAY_PWM: %d\n", ret);
		return 0;
	}

	uclass_foreach_dev(dev, uc) {
		ret = device_probe(dev);
		if (ret) {
			log_debug("Error probing %s: %d\n", dev->name, ret);
			continue;
		}
		display_pwm_set_backlight(dev, 255);
	}

	return 0;
}

UCLASS_DRIVER(display_pwm) = {
	.id		= UCLASS_DISPLAY_PWM,
	.name		= "display_pwm",
};

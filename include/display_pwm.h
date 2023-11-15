/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * header file for display pwm driver.
 *
 * Copyright (c) 2023 Predefine
 * Predefine <predefine@yandex.ru>
 */

#ifndef _display_pwm_h_
#define _display_pwm_h_

struct udevice;

/* struct display_pwm_ops: Operations for the Display PWM uclass */
struct display_pwm_ops {
    	int (*set_backlight)(struct udevice *dev, uint8_t level);
};

#define display_pwm_get_ops(dev)	((struct display_pwm_ops *)(dev)->driver->ops)

int display_pwm_set_backlight(struct udevice *dev, uint8_t level);

int initr_display_pwm(void);

#endif /* _display_pwm_h_ */

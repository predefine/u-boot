/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Configuration for MediaTek MT6580 SoC
 *
 * Copyright (C) 2023 Predefine
 * Author: Predefine <predefine@yandex.ru>
 */

#ifndef __MT6580_H
#define __MT6580_H

#include <linux/sizes.h>

/* MMC */
#define MMC_SUPPORTS_TUNING

/* DRAM */
#define CFG_SYS_SDRAM_BASE		0x80000000

/* This is needed for kernel booting */
#define FDT_HIGH			"0xac000000"

#define ENV_MEM_LAYOUT_SETTINGS				\
	"fdt_high=" FDT_HIGH "\0"			\
	"kernel_addr_r=0x84000000\0"			\
	"fdt_addr_r=" FDT_HIGH "\0"			\
	"fdtfile=" CONFIG_DEFAULT_FDT_FILE "\0"

#ifdef CONFIG_DISTRO_DEFAULTS

#define BOOT_TARGET_DEVICES(func)	\
		func(MMC, mmc, 1)

#include <config_distro_bootcmd.h>

/* Extra environment variables */
#define CFG_EXTRA_ENV_SETTINGS	\
	ENV_MEM_LAYOUT_SETTINGS		\
	BOOTENV

#endif /* ifdef CONFIG_DISTRO_DEFAULTS*/

#endif

/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2023
 */

#ifndef __PRESTIGIO_PMT3151_H
#define __PRESTIGIO_PMT3151_H

#include <linux/sizes.h>

#ifdef CONFIG_SPL_BUILD
#define CFG_MALLOC_F_ADDR		0x182000
/* For RAW image gives a error info not panic */
#endif

/* Initial environment variables */
#define CFG_EXTRA_ENV_SETTINGS					\
	"script=boot.scr\0"						\
	"fdt_addr=0x80000000\0"						\
	"fdt_high=0xffffffffffffffff\0"					\
	"initrd_addr=0x84000000\0"					\
	"initrd_high=0xffffffffffffffff\0"

#define CFG_SYS_INIT_RAM_ADDR	0x80000000
#define CFG_SYS_INIT_RAM_SIZE	0x80000


#define CFG_SYS_SDRAM_BASE		0x80000000
#define PHYS_SDRAM			0x40000000
#define PHYS_SDRAM_SIZE			0x40000000	/* 2 GiB DDR */

#define CFG_MXC_UART_BASE		UART_BASE_ADDR(1)

#define CFG_SYS_FSL_USDHC_NUM	2
#define CFG_SYS_FSL_ESDHC_ADDR	0

#endif

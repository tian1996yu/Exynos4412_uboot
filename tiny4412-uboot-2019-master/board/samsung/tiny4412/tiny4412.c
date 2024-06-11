// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2011 Samsung Electronics
 */

#include <common.h>
#include <asm/io.h>
#include <asm/gpio.h>
#include <asm/arch/cpu.h>
#include <asm/arch/mmc.h>
#include <asm/arch/periph.h>
#include <asm/arch/pinmux.h>
#include <usb.h>

DECLARE_GLOBAL_DATA_PTR;

u32 get_board_rev(void)
{
	return 0;
}

int exynos_init(void)
{
        printf("exynos_init\n");
	debug("---> ready to init usb3503\n");
	/* USB3503A Connect */
	gpio_request(EXYNOS4X12_GPIO_M33, "USB3503A Connect");
	/* USB3503A Reset */
	gpio_request(EXYNOS4X12_GPIO_M24, "USB3503A Reset");
	/* USB3503A Disconnect, Reset, Connect */
	gpio_direction_output(EXYNOS4X12_GPIO_M33, 0);
	gpio_direction_output(EXYNOS4X12_GPIO_M24, 0);
	gpio_direction_output(EXYNOS4X12_GPIO_M24, 1);
	gpio_direction_output(EXYNOS4X12_GPIO_M33, 1);
	return 0;
}

int board_usb_init(int index, enum usb_init_type init)
{
	return 0;
}

#ifdef CONFIG_BOARD_EARLY_INIT_F
int exynos_early_init_f(void)
{
	return 0;
}
#endif

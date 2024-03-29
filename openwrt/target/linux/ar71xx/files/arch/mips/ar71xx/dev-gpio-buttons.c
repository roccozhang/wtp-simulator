/*
 *  Atheros AR71xx GPIO button support
 *
 *  Copyright (C) 2008-2009 Gabor Juhos <juhosg@openwrt.org>
 *  Copyright (C) 2008 Imre Kaloz <kaloz@openwrt.org>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include "linux/init.h"
#include <linux/platform_device.h>

#include "dev-gpio-buttons.h"

void __init ar71xx_add_device_gpio_buttons(int id,
					   unsigned poll_interval,
					   unsigned nbuttons,
					   struct gpio_button *buttons)
{
	struct platform_device *pdev;
	struct gpio_buttons_platform_data pdata;
	struct gpio_button *p;
	int err;

	p = kmalloc(nbuttons * sizeof(*p), GFP_KERNEL);
	if (!p)
		return;

	memcpy(p, buttons, nbuttons * sizeof(*p));

	pdev = platform_device_alloc("gpio-buttons", id);
	if (!pdev)
		goto err_free_buttons;

	memset(&pdata, 0, sizeof(pdata));
	pdata.poll_interval = poll_interval;
	pdata.nbuttons = nbuttons;
	pdata.buttons = p;

	err = platform_device_add_data(pdev, &pdata, sizeof(pdata));
	if (err)
		goto err_put_pdev;


	err = platform_device_add(pdev);
	if (err)
		goto err_put_pdev;

	return;

err_put_pdev:
	platform_device_put(pdev);

err_free_buttons:
	kfree(p);
}

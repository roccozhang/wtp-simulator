/*
 *  Atheros AR71xx DSA switch device support
 *
 *  Copyright (C) 2008-2009 Gabor Juhos <juhosg@openwrt.org>
 *  Copyright (C) 2008 Imre Kaloz <kaloz@openwrt.org>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/platform_device.h>

#include <asm/mach-ar71xx/ar71xx.h>

#include "devices.h"
#include "dev-dsa.h"

static struct platform_device ar71xx_dsa_switch_device = {
	.name		= "dsa",
	.id		= 0,
};

void __init ar71xx_add_device_dsa(unsigned int id,
				  struct dsa_platform_data *d)
{
	int i;

	switch (id) {
	case 0:
		d->netdev = &ar71xx_eth0_device.dev;
		break;
	case 1:
		d->netdev = &ar71xx_eth1_device.dev;
		break;
	default:
		printk(KERN_ERR
			"ar71xx: invalid ethernet id %d for DSA switch\n",
			id);
		return;
	}

	for (i = 0; i < d->nr_chips; i++)
		d->chip[i].mii_bus = &ar71xx_mdio_device.dev;

	ar71xx_dsa_switch_device.dev.platform_data = d;

	platform_device_register(&ar71xx_dsa_switch_device);
}

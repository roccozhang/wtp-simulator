/*-
 * Copyright (c) 2002-2005 Sam Leffler, Errno Consulting
 * Copyright (c) 2004-2005 Atheros Communications, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer,
 *    without modification.
 * 2. Redistributions in binary form must reproduce at minimum a disclaimer
 *    similar to the "NO WARRANTY" disclaimer below ("Disclaimer") and any
 *    redistribution must be conditioned upon including a substantially
 *    similar Disclaimer requirement for further binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF NONINFRINGEMENT, MERCHANTIBILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGES.
 *
 * $Id: if_ath_pci.c 4134 2011-02-02 21:10:53Z proski $
 */
#include "opt_ah.h"

#ifndef EXPORT_SYMTAB
#define	EXPORT_SYMTAB
#endif

#if !defined(AUTOCONF_INCLUDED) && !defined(CONFIG_LOCALVERSION)
#include <linux/config.h>
#endif
#include <linux/version.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/if.h>
#include <linux/if_arp.h>
#include <linux/netdevice.h>
#include <linux/cache.h>

#include <linux/pci.h>

#include <asm/io.h>
#include <asm/uaccess.h>

#include "if_media.h"
#include <net80211/ieee80211_var.h>

#include "if_athvar.h"
#include "ah_devid.h"
#include "if_ath_pci.h"

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,4,0))
/*
 * PCI initialization uses Linux 2.4.x version and
 * older kernels do not support this
 */
#error Atheros PCI version requires at least Linux kernel version 2.4.0
#endif /* kernel < 2.4.0 */

struct ath_pci_softc {
	struct ath_softc	aps_sc;
#ifdef CONFIG_PM
	u32	aps_pmstate[16];
#endif
};

/*
 * Module glue.
 */
#include "release.h"
static char *version = RELEASE_VERSION;
static char *dev_info = "ath_pci";

#include <linux/ethtool.h>

/*
 * User a static table of PCI IDs for now.  While this is the
 * "new way" to do things, we may want to switch back to having
 * the HAL check them by defining a probe method.
 */
static struct pci_device_id ath_pci_id_table[] __devinitdata = {
	{ 0x168c, 0x0007, PCI_ANY_ID, PCI_ANY_ID },
	{ 0x168c, 0x0012, PCI_ANY_ID, PCI_ANY_ID },
	{ 0x168c, 0x0013, PCI_ANY_ID, PCI_ANY_ID },
	{ 0xa727, 0x0013, PCI_ANY_ID, PCI_ANY_ID }, /* 3com */
	{ 0x10b7, 0x0013, PCI_ANY_ID, PCI_ANY_ID }, /* 3com 3CRDAG675 */
	{ 0x168c, 0x1014, PCI_ANY_ID, PCI_ANY_ID }, /* IBM minipci 5212 */
	{ 0x168c, 0x101a, PCI_ANY_ID, PCI_ANY_ID }, /* some Griffin-Lite */
	{ 0x168c, 0x0015, PCI_ANY_ID, PCI_ANY_ID },
	{ 0x168c, 0x0016, PCI_ANY_ID, PCI_ANY_ID },
	{ 0x168c, 0x0017, PCI_ANY_ID, PCI_ANY_ID },
	{ 0x168c, 0x0018, PCI_ANY_ID, PCI_ANY_ID },
	{ 0x168c, 0x0019, PCI_ANY_ID, PCI_ANY_ID },
	{ 0x168c, 0x001a, PCI_ANY_ID, PCI_ANY_ID },
	{ 0x168c, 0x001b, PCI_ANY_ID, PCI_ANY_ID },
	{ 0x168c, 0x001c, PCI_ANY_ID, PCI_ANY_ID }, /* PCI Express 5424 */
	{ 0x168c, 0x001d, PCI_ANY_ID, PCI_ANY_ID }, /* PCI Express ???  */
	{ 0x168c, 0x0023, PCI_ANY_ID, PCI_ANY_ID },
	{ 0x168c, 0x0024, PCI_ANY_ID, PCI_ANY_ID },
	{ 0x168c, 0x0027, PCI_ANY_ID, PCI_ANY_ID },
#if 1 /* PCI based AR9280 doesn't work yet */
	{ 0x168c, 0x0029, PCI_ANY_ID, PCI_ANY_ID }, /* AR9280 PCI */
#endif
	{ 0x168c, 0x002a, PCI_ANY_ID, PCI_ANY_ID }, /* AR9280 PCI Express */
	{ 0x168c, 0x9013, PCI_ANY_ID, PCI_ANY_ID }, /* sonicwall */
	{ 0x168c, 0xff1a, PCI_ANY_ID, PCI_ANY_ID },
	{ 0 }
};

static u16 ath_devidmap[][2] = {
	{ 0x9013, 0x0013 },
	{ 0xff1a, 0x001a }
};

static const char ubnt[] = "Ubiquiti Networks";
/* { vendorname, cardname, vendorid, cardid, subsys vendorid, subsys id, poweroffset } */
static const struct ath_hw_detect cards[] = {
	{ ubnt, "XR2",     0x168c, 0x001b, 0x0777, 0x3002, 10 },
	{ ubnt, "XR2",     0x168c, 0x001b, 0x7777, 0x3002, 10 },
	{ ubnt, "XR2.3",   0x168c, 0x001b, 0x0777, 0x3b02, 10 },
	{ ubnt, "XR2.6",   0x168c, 0x001b, 0x0777, 0x3c02, 10 },
	{ ubnt, "XR3-2.8", 0x168c, 0x001b, 0x0777, 0x3b03, 10 },
	{ ubnt, "XR3-3.6", 0x168c, 0x001b, 0x0777, 0x3c03, 10 },
	{ ubnt, "XR3",     0x168c, 0x001b, 0x0777, 0x3003, 10 },
	{ ubnt, "XR4",     0x168c, 0x001b, 0x0777, 0x3004, 10 },
	{ ubnt, "XR5",     0x168c, 0x001b, 0x0777, 0x3005, 10 },
	{ ubnt, "XR5",     0x168c, 0x001b, 0x7777, 0x3005, 10 },
	{ ubnt, "XR7",     0x168c, 0x001b, 0x0777, 0x3007, 10 },
	{ ubnt, "XR9",     0x168c, 0x001b, 0x0777, 0x3009, 10 },
	{ ubnt, "SRC",     0x168c, 0x0013, 0x168c, 0x1042, 1 },
	{ ubnt, "SR2",     0x168c, 0x0013, 0x0777, 0x2041, 10 },
	{ ubnt, "SR4",     0x168c, 0x0013, 0x0777, 0x2004, 6 },
	{ ubnt, "SR4",     0x168c, 0x0013, 0x7777, 0x2004, 6 },
	{ ubnt, "SR4C",    0x168c, 0x0013, 0x0777, 0x1004, 6 },
	{ ubnt, "SR4C",    0x168c, 0x0013, 0x7777, 0x1004, 6 },
	{ ubnt, "SR5",     0x168c, 0x0013, 0x168c, 0x2042, 7 },
	{ ubnt, "SR9",     0x168c, 0x0013, 0x7777, 0x2009, 12 },
};

static int
ath_pci_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	resource_size_t phymem;
	void __iomem *mem;
	struct ath_pci_softc *sc;
	struct net_device *dev;
	const char *athname;
	u_int8_t csz;
	u32 val;
	u16 vdevice;
	int i;

	if (pci_enable_device(pdev)) {
		printk(KERN_ERR "%s: failed to enable PCI device\n", dev_info);
		return -EIO;
	}

	/* XXX 32-bit addressing only */
	if (pci_set_dma_mask(pdev, 0xffffffff)) {
		printk(KERN_ERR "%s: 32-bit DMA not available\n", dev_info);
		goto bad;
	}

	/*
	 * Cache line size is used to size and align various
	 * structures used to communicate with the hardware.
	 */
	pci_read_config_byte(pdev, PCI_CACHE_LINE_SIZE, &csz);
	if (csz == 0) {
		/*
		 * Linux 2.4.18 (at least) writes the cache line size
		 * register as a 16-bit wide register which is wrong.
		 * We must have this setup properly for rx buffer
		 * DMA to work so force a reasonable value here if it
		 * comes up zero.
		 */
		csz = L1_CACHE_BYTES / sizeof(u_int32_t);
		pci_write_config_byte(pdev, PCI_CACHE_LINE_SIZE, csz);
	}
	/*
	 * The default setting of latency timer yields poor results,
	 * set it to the value used by other systems.  It may be worth
	 * tweaking this setting more.
	 */
    pci_write_config_byte(pdev, PCI_LATENCY_TIMER, 0xa8);

	pci_set_master(pdev);

	/*
	 * Disable the RETRY_TIMEOUT register (0x41) to keep
	 * PCI Tx retries from interfering with C3 CPU state.
	 *
	 * Code taken from ipw2100 driver - jg
	 */
	pci_read_config_dword(pdev, 0x40, &val);
	if ((val & 0x0000ff00) != 0)
		pci_write_config_dword(pdev, 0x40, val & 0xffff00ff);

	phymem = pci_resource_start(pdev, 0);
	if (!request_mem_region(phymem, pci_resource_len(pdev, 0), "ath")) {
		printk(KERN_ERR "%s: cannot reserve PCI memory region\n", dev_info);
		goto bad;
	}

	mem = ioremap(phymem, pci_resource_len(pdev, 0));
	if (!mem) {
		printk(KERN_ERR "%s: cannot remap PCI memory region\n", dev_info);
		goto bad1;
	}

	dev = alloc_netdev(sizeof(struct ath_pci_softc), "wifi%d", ether_setup);
	if (dev == NULL) {
		printk(KERN_ERR "%s: no memory for device state\n", dev_info);
		goto bad2;
	}
	sc = netdev_priv(dev);
	sc->aps_sc.sc_dev = dev;
	sc->aps_sc.sc_iobase = mem;

	/*
	 * Mark the device as detached to avoid processing
	 * interrupts until setup is complete.
	 */
	sc->aps_sc.sc_invalid = 1;

	if (dev_alloc_name(dev, dev->name) < 0) {
		printk(KERN_ERR "%s: cannot allocate name\n", dev_info);
		goto bad3;
	}

	dev->irq = pdev->irq;

	SET_MODULE_OWNER(dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	sc->aps_sc.sc_bdev = (void *)pdev;

	pci_set_drvdata(pdev, dev);

	if (request_irq(dev->irq, ath_intr, IRQF_SHARED, dev->name, dev)) {
		printk(KERN_WARNING "%s: request_irq failed\n", dev->name);
		goto bad3;
	}

	/* looking for device type from broken device id */
	vdevice = id->device;
	for (i = 0; i < ARRAY_SIZE(ath_devidmap); i++) {
		if (id->device == ath_devidmap[i][0]) {
			vdevice = ath_devidmap[i][1];
			break;
		}
	}



	if ((i = ath_attach(vdevice, dev, NULL)) != 0) {
		printk(KERN_ERR "%s: ath_attach failed: %d\n", dev_info, i);
		goto bad4;
	}

	athname = ath_hal_probe(id->vendor, vdevice);
	printk(KERN_INFO "%s: %s: %s: mem=0x%llx, irq=%d\n",
		dev_info, dev->name, athname ? athname : "Atheros ???", 
		(unsigned long long)phymem, dev->irq);

	ath_hw_detect(&sc->aps_sc, cards, ARRAY_SIZE(cards),
		pdev->vendor, pdev->device,
		pdev->subsystem_vendor, pdev->subsystem_device);

	if (vdevice == AR5416_DEVID_PCIE)
		sc->aps_sc.sc_dmasize_stomp = 1;

	/* ready to process interrupts */
	sc->aps_sc.sc_invalid = 0;

	return 0;
bad4:
	free_irq(dev->irq, dev);
bad3:
	free_netdev(dev);
bad2:
	iounmap(mem);
bad1:
	release_mem_region(phymem, pci_resource_len(pdev, 0));
bad:
	pci_disable_device(pdev);
	return (-ENODEV);
}

static void
ath_pci_remove(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct ath_pci_softc *sc = netdev_priv(dev);

	ath_detach(dev);
	if (dev->irq)
		free_irq(dev->irq, dev);
	iounmap(sc->aps_sc.sc_iobase);
	release_mem_region(pci_resource_start(pdev, 0), pci_resource_len(pdev, 0));
	pci_disable_device(pdev);
	free_netdev(dev);
}

#ifdef CONFIG_PM
static int
ath_pci_suspend(struct pci_dev *pdev, pm_message_t state)
{
	struct net_device *dev = pci_get_drvdata(pdev);

	ath_suspend(dev);
	PCI_SAVE_STATE(pdev, ((struct ath_pci_softc *)netdev_priv(dev))->aps_pmstate);
	pci_disable_device(pdev);
	return pci_set_power_state(pdev, PCI_D3hot);
}

static int
ath_pci_resume(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	u32 val;
	int err;

	err = pci_set_power_state(pdev, PCI_D0);
	if (err)
		return err;

	/* XXX - Should this return nonzero on fail? */
	PCI_RESTORE_STATE(pdev,	((struct ath_pci_softc *)netdev_priv(dev))->aps_pmstate);

	err = pci_enable_device(pdev);
	if (err)
		return err;

	pci_set_master(pdev);
	/*
	 * Suspend/Resume resets the PCI configuration space, so we have to
	 * re-disable the RETRY_TIMEOUT register (0x41) to keep
	 * PCI Tx retries from interfering with C3 CPU state
	 *
	 * Code taken from ipw2100 driver - jg
	 */
	pci_read_config_dword(pdev, 0x40, &val);
	if ((val & 0x0000ff00) != 0)
		pci_write_config_dword(pdev, 0x40, val & 0xffff00ff);
	ath_resume(dev);

	return 0;
}
#endif /* CONFIG_PM */

MODULE_DEVICE_TABLE(pci, ath_pci_id_table);

static struct pci_driver ath_pci_driver = {
	.name		= "ath_pci",
	.id_table	= ath_pci_id_table,
	.probe		= ath_pci_probe,
	.remove		= ath_pci_remove,
#ifdef CONFIG_PM
	.suspend	= ath_pci_suspend,
	.resume		= ath_pci_resume,
#endif /* CONFIG_PM */
	/* Linux 2.4.6 has save_state and enable_wake that are not used here */
};

int
ath_ioctl_ethtool(struct ath_softc *sc, int cmd, void __user *addr)
{
	struct ethtool_drvinfo info;

	if (cmd != ETHTOOL_GDRVINFO)
		return -EOPNOTSUPP;
	memset(&info, 0, sizeof(info));
	info.cmd = cmd;
	strncpy(info.driver, dev_info, sizeof(info.driver) - 1);
	strncpy(info.version, version, sizeof(info.version) - 1);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,4,22)
	/* include the device name so later versions of kudzu DTRT */
	strncpy(info.bus_info, pci_name((struct pci_dev *)sc->sc_bdev),
		sizeof(info.bus_info) - 1);
#endif
	return copy_to_user(addr, &info, sizeof(info)) ? -EFAULT : 0;
}

MODULE_AUTHOR("Errno Consulting, Sam Leffler");
MODULE_DESCRIPTION("Support for Atheros 802.11 wireless LAN cards.");
#ifdef MODULE_VERSION
MODULE_VERSION(RELEASE_VERSION);
#endif
MODULE_SUPPORTED_DEVICE("Atheros WLAN cards");
#ifdef MODULE_LICENSE
MODULE_LICENSE("Dual BSD/GPL");
#endif

static int __init
init_ath_pci(void)
{
	int status;
	ath_sysctl_register();
	if ((status = pci_register_driver(&ath_pci_driver))) {
		ath_sysctl_unregister();
		return (status);
	}
	return (0);
}
module_init(init_ath_pci);

static void __exit
exit_ath_pci(void)
{
	ath_sysctl_unregister();
	pci_unregister_driver(&ath_pci_driver);
}
module_exit(exit_ath_pci);

/* return bus cachesize in 4B word units */
void
bus_read_cachesize(struct ath_softc *sc, u_int8_t *csz)
{
	pci_read_config_byte(sc->sc_bdev, PCI_CACHE_LINE_SIZE, csz);
}

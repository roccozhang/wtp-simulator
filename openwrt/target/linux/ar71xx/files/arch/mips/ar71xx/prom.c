/*
 *  Atheros AR71xx SoC specific prom routines
 *
 *  Copyright (C) 2008-2009 Gabor Juhos <juhosg@openwrt.org>
 *  Copyright (C) 2008 Imre Kaloz <kaloz@openwrt.org>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/string.h>

#include <asm/bootinfo.h>
#include <asm/addrspace.h>
#include <asm/fw/myloader/myloader.h>

#include <asm/mach-ar71xx/ar71xx.h>

static inline int is_valid_ram_addr(void *addr)
{
	if (((u32) addr > KSEG0) &&
	    ((u32) addr < (KSEG0 + AR71XX_MEM_SIZE_MAX)))
		return 1;

	if (((u32) addr > KSEG1) &&
	    ((u32) addr < (KSEG1 + AR71XX_MEM_SIZE_MAX)))
		return 1;

	return 0;
}

static void __init ar71xx_prom_append_cmdline(const char *name,
					      const char *value)
{
	char buf[COMMAND_LINE_SIZE];

	snprintf(buf, sizeof(buf), " %s=%s", name, value);
	strlcat(arcs_cmdline, buf, sizeof(arcs_cmdline));
}

static void __init ar71xx_prom_find_env(char **envp, const char *name)
{
	int len = strlen(name);
	char **p;

	if (!is_valid_ram_addr(envp))
		return;

	for (p = envp; is_valid_ram_addr(*p); p++) {
		if (strncmp(name, *p, len) == 0 && (*p)[len] == '=') {
			ar71xx_prom_append_cmdline(name, *p + len + 1);
			break;
		}

		/* RedBoot env comes in pointer pairs - key, value */
		if (strncmp(name, *p, len) == 0 && (*p)[len] == 0)
			if (is_valid_ram_addr(*(++p))) {
				ar71xx_prom_append_cmdline(name, *p);
				break;
			}
	}
}

static int __init ar71xx_prom_init_myloader(void)
{
	struct myloader_info *mylo;
	char mac_buf[32];
	char *mac;

	mylo = myloader_get_info();
	if (!mylo)
		return 0;

	switch (mylo->did) {
	case DEVID_COMPEX_WP543:
		ar71xx_prom_append_cmdline("board", "WP543");
		break;
	default:
		printk(KERN_WARNING "prom: unknown device id: %x\n",
				mylo->did);
		return 0;
	}

	mac = mylo->macs[0];
	snprintf(mac_buf, sizeof(mac_buf), "%02x:%02x:%02x:%02x:%02x:%02x",
		 mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

	ar71xx_prom_append_cmdline("ethaddr", mac_buf);

	return 1;
}

#ifdef CONFIG_IMAGE_CMDLINE_HACK
extern char __image_cmdline[];

static int __init ar71xx_use__image_cmdline(void)
{
	char *p = __image_cmdline;
	int replace = 0;

	if (*p == '-') {
		replace = 1;
		p++;
	}

	if (*p == '\0')
		return 0;

	if (replace) {
		strlcpy(arcs_cmdline, p, sizeof(arcs_cmdline));
	} else {
		strlcat(arcs_cmdline, " ", sizeof(arcs_cmdline));
		strlcat(arcs_cmdline, p, sizeof(arcs_cmdline));
	}

	return 1;
}
#else
static int inline ar71xx_use__image_cmdline(void) { return 0; }
#endif

static __init void ar71xx_prom_init_cmdline(int argc, char **argv)
{
	int i;

	if (ar71xx_use__image_cmdline())
		return;

	if (!is_valid_ram_addr(argv))
		return;

	for (i = 0; i < argc; i++)
		if (is_valid_ram_addr(argv[i])) {
			strlcat(arcs_cmdline, " ", sizeof(arcs_cmdline));
			strlcat(arcs_cmdline, argv[i], sizeof(arcs_cmdline));
		}
}

void __init prom_init(void)
{
	char **envp;

	printk(KERN_DEBUG "prom: fw_arg0=%08x, fw_arg1=%08x, "
			"fw_arg2=%08x, fw_arg3=%08x\n",
			(unsigned int)fw_arg0, (unsigned int)fw_arg1,
			(unsigned int)fw_arg2, (unsigned int)fw_arg3);


	if (ar71xx_prom_init_myloader())
		return;

	ar71xx_prom_init_cmdline(fw_arg0, (char **)fw_arg1);

	envp = (char **)fw_arg2;
	ar71xx_prom_find_env(envp, "board");
	ar71xx_prom_find_env(envp, "ethaddr");
}

void __init prom_free_prom_memory(void)
{
	/* We do not have to prom memory to free */
}

/*
 * Copyright (C) 2015 CompuLab LTD. 
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <linux/regmap.h>
#include <linux/mfd/syscon.h>
#include <linux/mfd/syscon/imx6q-iomuxc-gpr.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>

static void __init cl_som_imx6ul_enet_clk_init(void)
{
	struct regmap *gpr;

	gpr = syscon_regmap_lookup_by_compatible("fsl,imx6ul-iomuxc-gpr");
	if (!IS_ERR(gpr))
		regmap_update_bits(gpr, IOMUXC_GPR1, IMX6UL_GPR1_ENET_CLK_DIR,
				   1 << 13);
	else
		pr_err("failed to find fsl,imx6ul-iomux-gpr regmap\n");

}

static int __init cl_som_imx6ul_init(void)
{
	struct device_node *np;

	np = of_find_compatible_node(NULL, NULL, "compulab,cl-som-imx6ul");

	if (!np) {
		pr_err("failed to find compulab,cl-som-imx6ul\n");
		return -ENODEV;
	}

	cl_som_imx6ul_enet_clk_init();

	return 0;
}
subsys_initcall(cl_som_imx6ul_init);

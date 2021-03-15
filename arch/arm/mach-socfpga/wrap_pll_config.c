/*
 * Copyright (C) 2015 Marek Vasut <marex@denx.de>
 *
 * SPDX-License-Identifier:    GPL-2.0+
 */

#include <common.h>
#include <asm/arch/clock_manager.h>
#include <qts/pll_config.h>

#define MAIN_VCO_BASE (					\
	(CONFIG_HPS_MAINPLLGRP_VCO_DENOM <<		\
		CLKMGR_MAINPLLGRP_VCO_DENOM_OFFSET) |	\
	(CONFIG_HPS_MAINPLLGRP_VCO_NUMER <<		\
		CLKMGR_MAINPLLGRP_VCO_NUMER_OFFSET)	\
	)

#define PERI_VCO_BASE (					\
	(CONFIG_HPS_PERPLLGRP_VCO_PSRC <<		\
		CLKMGR_PERPLLGRP_VCO_PSRC_OFFSET) |	\
	(CONFIG_HPS_PERPLLGRP_VCO_DENOM <<		\
		CLKMGR_PERPLLGRP_VCO_DENOM_OFFSET) |	\
	(CONFIG_HPS_PERPLLGRP_VCO_NUMER <<		\
		CLKMGR_PERPLLGRP_VCO_NUMER_OFFSET)	\
	)

#define SDR_VCO_BASE (					\
	(CONFIG_HPS_SDRPLLGRP_VCO_SSRC <<		\
		CLKMGR_SDRPLLGRP_VCO_SSRC_OFFSET) |	\
	(CONFIG_HPS_SDRPLLGRP_VCO_DENOM <<		\
		CLKMGR_SDRPLLGRP_VCO_DENOM_OFFSET) |	\
	(CONFIG_HPS_SDRPLLGRP_VCO_NUMER <<		\
		CLKMGR_SDRPLLGRP_VCO_NUMER_OFFSET)	\
	)

static const struct cm_config cm_default_cfg = {
	/* main group */
	MAIN_VCO_BASE,
	(CONFIG_HPS_MAINPLLGRP_MPUCLK_CNT <<
		CLKMGR_MAINPLLGRP_MPUCLK_CNT_OFFSET),
	(CONFIG_HPS_MAINPLLGRP_MAINCLK_CNT <<
		CLKMGR_MAINPLLGRP_MAINCLK_CNT_OFFSET),
	(CONFIG_HPS_MAINPLLGRP_DBGATCLK_CNT <<
		CLKMGR_MAINPLLGRP_DBGATCLK_CNT_OFFSET),
	(CONFIG_HPS_MAINPLLGRP_MAINQSPICLK_CNT <<
		CLKMGR_MAINPLLGRP_MAINQSPICLK_CNT_OFFSET),
	(CONFIG_HPS_MAINPLLGRP_MAINNANDSDMMCCLK_CNT <<
		CLKMGR_PERPLLGRP_PERNANDSDMMCCLK_CNT_OFFSET),
	(CONFIG_HPS_MAINPLLGRP_CFGS2FUSER0CLK_CNT <<
		CLKMGR_MAINPLLGRP_CFGS2FUSER0CLK_CNT_OFFSET),
	(CONFIG_HPS_MAINPLLGRP_MAINDIV_L3MPCLK <<
		CLKMGR_MAINPLLGRP_MAINDIV_L3MPCLK_OFFSET) |
	(CONFIG_HPS_MAINPLLGRP_MAINDIV_L3SPCLK <<
		CLKMGR_MAINPLLGRP_MAINDIV_L3SPCLK_OFFSET) |
	(CONFIG_HPS_MAINPLLGRP_MAINDIV_L4MPCLK <<
		CLKMGR_MAINPLLGRP_MAINDIV_L4MPCLK_OFFSET) |
	(CONFIG_HPS_MAINPLLGRP_MAINDIV_L4SPCLK <<
		CLKMGR_MAINPLLGRP_MAINDIV_L4SPCLK_OFFSET),
	(CONFIG_HPS_MAINPLLGRP_DBGDIV_DBGATCLK <<
		CLKMGR_MAINPLLGRP_DBGDIV_DBGATCLK_OFFSET) |
	(CONFIG_HPS_MAINPLLGRP_DBGDIV_DBGCLK <<
		CLKMGR_MAINPLLGRP_DBGDIV_DBGCLK_OFFSET),
	(CONFIG_HPS_MAINPLLGRP_TRACEDIV_TRACECLK <<
		CLKMGR_MAINPLLGRP_TRACEDIV_TRACECLK_OFFSET),
	(CONFIG_HPS_MAINPLLGRP_L4SRC_L4MP <<
		CLKMGR_MAINPLLGRP_L4SRC_L4MP_OFFSET) |
	(CONFIG_HPS_MAINPLLGRP_L4SRC_L4SP <<
		CLKMGR_MAINPLLGRP_L4SRC_L4SP_OFFSET),

	/* peripheral group */
	PERI_VCO_BASE,
	(CONFIG_HPS_PERPLLGRP_EMAC0CLK_CNT <<
		CLKMGR_PERPLLGRP_EMAC0CLK_CNT_OFFSET),
	(CONFIG_HPS_PERPLLGRP_EMAC1CLK_CNT <<
		CLKMGR_PERPLLGRP_EMAC1CLK_CNT_OFFSET),
	(CONFIG_HPS_PERPLLGRP_PERQSPICLK_CNT <<
		CLKMGR_PERPLLGRP_PERQSPICLK_CNT_OFFSET),
	(CONFIG_HPS_PERPLLGRP_PERNANDSDMMCCLK_CNT <<
		CLKMGR_PERPLLGRP_PERNANDSDMMCCLK_CNT_OFFSET),
	(CONFIG_HPS_PERPLLGRP_PERBASECLK_CNT <<
		CLKMGR_PERPLLGRP_PERBASECLK_CNT_OFFSET),
	(CONFIG_HPS_PERPLLGRP_S2FUSER1CLK_CNT <<
		CLKMGR_PERPLLGRP_S2FUSER1CLK_CNT_OFFSET),
	(CONFIG_HPS_PERPLLGRP_DIV_USBCLK <<
		CLKMGR_PERPLLGRP_DIV_USBCLK_OFFSET) |
	(CONFIG_HPS_PERPLLGRP_DIV_SPIMCLK <<
		CLKMGR_PERPLLGRP_DIV_SPIMCLK_OFFSET) |
	(CONFIG_HPS_PERPLLGRP_DIV_CAN0CLK <<
		CLKMGR_PERPLLGRP_DIV_CAN0CLK_OFFSET) |
	(CONFIG_HPS_PERPLLGRP_DIV_CAN1CLK <<
		CLKMGR_PERPLLGRP_DIV_CAN1CLK_OFFSET),
	(CONFIG_HPS_PERPLLGRP_GPIODIV_GPIODBCLK <<
		CLKMGR_PERPLLGRP_GPIODIV_GPIODBCLK_OFFSET),
	(CONFIG_HPS_PERPLLGRP_SRC_QSPI <<
		CLKMGR_PERPLLGRP_SRC_QSPI_OFFSET) |
	(CONFIG_HPS_PERPLLGRP_SRC_NAND <<
		CLKMGR_PERPLLGRP_SRC_NAND_OFFSET) |
	(CONFIG_HPS_PERPLLGRP_SRC_SDMMC <<
		CLKMGR_PERPLLGRP_SRC_SDMMC_OFFSET),

	/* sdram pll group */
	SDR_VCO_BASE,
	(CONFIG_HPS_SDRPLLGRP_DDRDQSCLK_PHASE <<
		CLKMGR_SDRPLLGRP_DDRDQSCLK_PHASE_OFFSET) |
	(CONFIG_HPS_SDRPLLGRP_DDRDQSCLK_CNT <<
		CLKMGR_SDRPLLGRP_DDRDQSCLK_CNT_OFFSET),
	(CONFIG_HPS_SDRPLLGRP_DDR2XDQSCLK_PHASE <<
		CLKMGR_SDRPLLGRP_DDR2XDQSCLK_PHASE_OFFSET) |
	(CONFIG_HPS_SDRPLLGRP_DDR2XDQSCLK_CNT <<
		CLKMGR_SDRPLLGRP_DDR2XDQSCLK_CNT_OFFSET),
	(CONFIG_HPS_SDRPLLGRP_DDRDQCLK_PHASE <<
		CLKMGR_SDRPLLGRP_DDRDQCLK_PHASE_OFFSET) |
	(CONFIG_HPS_SDRPLLGRP_DDRDQCLK_CNT <<
		CLKMGR_SDRPLLGRP_DDRDQCLK_CNT_OFFSET),
	(CONFIG_HPS_SDRPLLGRP_S2FUSER2CLK_PHASE <<
		CLKMGR_SDRPLLGRP_S2FUSER2CLK_PHASE_OFFSET) |
	(CONFIG_HPS_SDRPLLGRP_S2FUSER2CLK_CNT <<
		CLKMGR_SDRPLLGRP_S2FUSER2CLK_CNT_OFFSET),
};

const struct cm_config * const cm_get_default_config(void)
{
	return &cm_default_cfg;
}

const unsigned int cm_get_osc_clk_hz(const int osc)
{
	if (osc == 1)
		return CONFIG_HPS_CLK_OSC1_HZ;
	else if (osc == 2)
		return CONFIG_HPS_CLK_OSC2_HZ;
	else
		return 0;
}

const unsigned int cm_get_f2s_per_ref_clk_hz(void)
{
	return CONFIG_HPS_CLK_F2S_PER_REF_HZ;
}

const unsigned int cm_get_f2s_sdr_ref_clk_hz(void)
{
	return CONFIG_HPS_CLK_F2S_SDR_REF_HZ;
}

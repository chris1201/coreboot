/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2012 Advanced Micro Devices, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <arch/acpi.h>
#include <bootstate.h>
#include <console/console.h>

#include "agesawrapper.h"
#include <northbridge/amd/agesa/agesawrapper_call.h>

#if IS_ENABLED(CONFIG_HUDSON_IMC_FWM)
#include <southbridge/amd/agesa/hudson/imc.h>
#endif
#if CONFIG_AMD_SB_CIMX
#include <sb_cimx.h>
#endif

void get_bus_conf(void);

static void agesawrapper_post_device(void *unused)
{
	if (acpi_is_wakeup_s3())
		return;

	AGESAWRAPPER(amdinitlate);

	/* Preparation for write_tables(). */
	get_bus_conf();

#if IS_ENABLED(CONFIG_HUDSON_IMC_FWM)
	/* AMD AGESA does not enable thermal zone, so we enable it here. */
	enable_imc_thermal_zone();
#endif

#if CONFIG_AMD_SB_CIMX
	sb_Late_Post();
#endif
	if (!acpi_s3_resume_allowed())
		return;

	AGESAWRAPPER(amdS3Save);
}

BOOT_STATE_INIT_ENTRIES(agesa_bscb) = {
	BOOT_STATE_INIT_ENTRY(BS_POST_DEVICE, BS_ON_EXIT,
	                      agesawrapper_post_device, NULL),
};

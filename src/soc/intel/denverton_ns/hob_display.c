/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2017 Intel Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <console/console.h>
#include <fsp/util.h>
#include <lib.h>

static const uint8_t fsp_hob_resource_owner_graphics_guid[16] = {
	0xa7, 0x3a, 0x7c, 0x9c, 0x32, 0x55, 0x17, 0x49,
	0x82, 0xb9, 0x56, 0xa5, 0xf3, 0xe6, 0x2a, 0x07
};

static const uint8_t fsp_hob_resource_owner_fiamux_guid[16] = {
	0x2e, 0x49, 0xad, 0x26, 0x51, 0xf9, 0x43, 0x4e,
	0xbc, 0x72, 0x22, 0x76, 0x58, 0xb1, 0xf6, 0x23
};

static const uint8_t fsp_hob_fast_boot_checker_guid[16] = {
	0x7b, 0xf0, 0x97, 0x78, 0xda, 0x0c, 0xe3, 0x40,
	0xb4, 0xe4, 0x51, 0x5f, 0x47, 0x3b, 0x04, 0xb6
};

struct guid_name_map {
	const void *guid;
	const char *name;
};

static const struct guid_name_map  guid_names[] = {
	{ fsp_hob_resource_owner_graphics_guid,
		"FSP_HOB_RESOURCE_OWNER_GRAPHICS_GUID" },
	{ fsp_hob_resource_owner_fiamux_guid,
		"FSP_HOB_RESOURCE_OWNER_FIAMUX_GUID" },
	{ fsp_hob_fast_boot_checker_guid,
		"FSP_HOB_FAST_BOOT_CHECKER_GUID" },
};

const char *soc_get_hob_type_name(
	const struct hob_header *hob)
{
	return NULL;
}

const char *soc_get_guid_name(const uint8_t *guid)
{
	size_t index;

	/* Compare the GUID values in this module */
	for (index = 0; index < ARRAY_SIZE(guid_names); index++)
		if (fsp_guid_compare(guid, guid_names[index].guid))
			return guid_names[index].name;

	return NULL;
}

void soc_display_hob(const struct hob_header *hob)
{
	hexdump(hob, hob->length);
}

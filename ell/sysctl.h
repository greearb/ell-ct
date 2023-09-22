/*
 *
 *  Embedded Linux library
 *
 *  Copyright (C) 2022  Intel Corporation. All rights reserved.
 *  Copyright (C) 2023  Cruise LLC. All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef __ELL_SYSCTL_H
#define __ELL_SYSCTL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int l_sysctl_get_u32(uint32_t *out_v, const char *format, ...)
			__attribute__((format(printf, 2, 3)));
int l_sysctl_set_u32(uint32_t v, const char *format, ...)
			__attribute__((format(printf, 2, 3)));

#ifdef __cplusplus
}
#endif

#endif /* __ELL_SYSCTL_H */

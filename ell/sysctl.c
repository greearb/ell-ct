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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#define _GNU_SOURCE
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "sysctl.h"
#include "useful.h"
#include "util.h"
#include "private.h"

static int sysctl_write(const char *file, const void *value, size_t len)
{
	int fd;
	ssize_t r;

	fd = L_TFR(open(file, O_WRONLY));
	if (unlikely(fd < 0))
		return -errno;

	r = L_TFR(write(fd, value, len));
	if (r < 0)
		r = -errno;
	else
		r = 0;

	close(fd);
	return r;
}

static int sysctl_read(const char *file, void *dest, size_t len)
{
	int fd;
	ssize_t r;

	fd = L_TFR(open(file, O_RDONLY));
	if (unlikely(fd < 0))
		return -errno;

	r = L_TFR(read(fd, dest, len));
	if (unlikely(r < 0))
		r = -errno;

	close(fd);
	return r;
}

LIB_EXPORT int l_sysctl_get_u32(uint32_t *out_v, const char *format, ...)
{
	_auto_(l_free) char *filename = NULL;
	va_list ap;
	char valuestr[64];
	int r;

	va_start(ap, format);
	filename = l_strdup_vprintf(format, ap);
	va_end(ap);

	r = sysctl_read(filename, valuestr, sizeof(valuestr) - 1);
	if (r < 0)
		return r;

	while (r > 0 && L_IN_SET(valuestr[r - 1], '\n', '\r', '\t', ' '))
		r--;

	valuestr[r] = '\0';

	return l_safe_atou32(valuestr, out_v);
}

LIB_EXPORT int l_sysctl_set_u32(uint32_t v, const char *format, ...)
{
	_auto_(l_free) char *filename = NULL;
	va_list ap;
	char valuestr[64];
	size_t len;

	va_start(ap, format);
	filename = l_strdup_vprintf(format, ap);
	va_end(ap);

	len = snprintf(valuestr, sizeof(valuestr), "%u", v);

	return sysctl_write(filename, valuestr, len);
}

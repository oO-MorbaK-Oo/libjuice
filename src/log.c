/**
 * Copyright (c) 2020 Paul-Louis Ageneau
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "log.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

static const char *log_level_names[] = {
  "VERBOSE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

static juice_log_level_t log_level = JUICE_LOG_LEVEL_WARN;

void juice_log_set_level(juice_log_level_t level) { log_level = level; }

void juice_log_write(juice_log_level_t level, const char *file, int line,
                     const char *fmt, ...) {
	if (level < log_level) return;

	time_t t = time(NULL);
	struct tm *lt = localtime(&t);
	char buffer[16];
	if (strftime(buffer, 16, "%H:%M:%S", lt) == 0)
		buffer[0] = '\0';

	fprintf(stderr, "%s %-7s %s:%d: ", buffer, log_level_names[level], file,
	        line);

	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	fprintf(stderr, "\n");
	fflush(stderr);
}

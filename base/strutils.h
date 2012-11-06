/*
 * HEX Programming Language
 * Copyright (C) 2012  Yanzheng Li
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Helper functions on null-terminated strings. */

#ifndef _STRUTILS_H_
#define _STRUTILS_H_

#include <stddef.h>


/*
 * Converts a string to upper case.
 */
char* strtoupper(char *s);

/*
 * Converts a string to lower case.
 */
char* strtolower(char *s);


/*
 * Copies the source to the destination.
 * If the destination length is shorter than the source
 * length, then the destination is re-allocated.
 */
char* strcpy_hard(char *dst, const char *src);


/*
 * Trims whitespaces on the given null-terminated string.
 * The original string is modified and returned.
 */
char* strtrim(char *s);

/*
 * Copy 'src' to 'dst' of length 'size'.  At most size-1 characters
 * will be copied.  Always NULL terminates (unless size == 0).
 * Returns strlen(src); if retval >= size, truncation occurred.
 */
size_t strlcpy(char *dst, const char *src, size_t size);


/*
 * A strcpy which ensures NULL terminated string and never overruns the output.
 */
char* strncpy_safe(char *dst, const char *src, size_t size);

/*
 * Integer to string, with base 2, 8 and 16 formatting.
 */
char* itoa_fmt(int value, char *str, int base, int capital);


#endif /* _STRUTILS_H_ */
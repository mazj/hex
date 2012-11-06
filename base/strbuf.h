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

/* String buffer */

#ifndef _STRBUF_H_
#define _STRBUF_H_


#include <stddef.h>
#include <stdarg.h>

typedef struct HexStrbuf_s *Strbuf;


void strbuf_append(Strbuf strbuf, const char *in_str);

void strbuf_appendn(Strbuf strbuf, const char *in_str, size_t len);

char* strbuf_string(Strbuf strbuf);

void strbuf_empty(Strbuf strbuf);

size_t strbuf_len(Strbuf strbuf);

void strbuf_constructor(Strbuf strbuf);

void strbuf_destructor(Strbuf strbuf);

void strbuf_reverse(Strbuf strbuf);

void strbuf_set_alloc_size(size_t size);

size_t strbuf_get_allocated_size(Strbuf strbuf);

void strbuf_append_printf(Strbuf strbuf, const char *in_str, ...);


#endif /* _STRBUF_H_ */
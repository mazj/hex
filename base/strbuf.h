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


/* Generic string buffer */

#ifndef _STRBUF_H_
#define _STRBUF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

typedef struct HexStrbuf_s *Strbuf;

Strbuf strbuf_create();

void strbuf_free(Strbuf *strbuf);

void strbuf_empty(Strbuf strbuf);

size_t strbuf_len(Strbuf strbuf);

char* strbuf_cstr(Strbuf strbuf);

size_t strbuf_capacity(Strbuf strbuf);

int strbuf_append(Strbuf strbuf, const char *in_str);


#ifdef __cplusplus
}
#endif


#endif /* _STRBUF_H_ */

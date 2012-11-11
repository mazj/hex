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


#ifndef _TTable_H_
#define _TTable_H_

#include <stddef.h>
#include "uuid.h"

typedef uuid_t hex_type_id_t;

typedef struct HexTtableEntry {
  hex_type_id_t type_id;
  struct HexType type;
} *TtableEntry;

Ttable ttable_create();

size_t ttable_size();

void* ttable_put(Ttale ttable, TtableEntry entry);

int ttable_remove(Ttable ttable, hex_type_id_t type_id);

TtableEntry ttable_lookup(Ttable ttable, char *type_name);

size_t ttable_bucketcount(Ttable ttable);

int ttable_capacity(Ttable ttable);


#endif /* _TTable_H_ */

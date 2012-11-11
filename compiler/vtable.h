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

#ifndef _VTABLE_H_
#define _VTABLE_H_

#include <stddef.h>
#include "scope.h"
#include "token_loc.h"

typedef struct HexVtableEntry {
  hex_scope_id_t scope_id;
  hex_scope_type_t scope_type;
  TokenLoc token_loc;
  char *var_name;
  void *var_type;
} *VtableEntry;

typedef struct HexVtable *Vtable;

Vtable vtable_create();

size_t vtable_size();

void* vtable_put(Vtable vtable, hex_scope_type_t scope_type,
    hex_scope_id_t scope_id, char *var_name, TokenLoc token_loc, void *var_type);

void* vtable_put(Vtable vtable, VtableEntry var);

int vtable_remove(Vtbale vtable, hex_scope_id scope_id);

VtableEntry vtable_lookup(Vtable vtable, char *var_name, hex_scope_id_t scope_id);

VtableEntry vtable_lookup_global(Vtable vtable, char *var_name, hex_scope_id_t scope_id);

size_t vtable_bucketcount(Vtable vtable);

size_t vtable_capacity(Vtable vtable);


#endif /* _VTABLE_H_ */

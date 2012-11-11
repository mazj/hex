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

#ifndef _FTABLE_H_
#define _FTABLE_H_

#include <stddef.h>
#include "token_loc.h"
#include "ast.h"
#include "uuid.h"

typedef uuid_t hex_func_id_t;

typedef struct HexFtableEntry {
  hex_func_id_t func_id;
  char *func_name;
  hex_type_id_t return_type;
  ParameterList params;
  TokenLoc token_loc;
  int flag;
} *FtableEntry;

typedef struct HexFtable *Ftable;

Ftable ftable_create();

FtableEntry ftable_create_entry(char *func_name,
  ParameterList params, hex_type_id_t return_type, TokenLoc token_loc);

size_t ftable_size();

void* ftable_put(Ftable ftable, FtableEntry func);

int ftable_remove(Ftbale ftable, hex_func_id_t func_id);

FtableEntry ftable_lookup_by_id(Ftable ftable, hex_func_id_t fund_id);

FtableEntry ftable_lookup_by_name(Ftable ftable, char *func_name);

FtableEntry ftable_lookup_by_signature(Ftable ftable, char *func_name, ParameterList params);

size_t ftable_bucketcount(Ftable ftable);

size_t ftable_capacity(Ftable ftable);


#endif /* _FTABLE_H_ */
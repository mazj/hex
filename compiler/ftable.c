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

#include <errno.h>
#include "memory.h"
#include "assert.h"
#include "utils.h"
#include "hashmap.h"
#include "ftable.h"


#define FTABLE_DEFAULT_CAPACITY 10


struct HexFtable {
  Hashmap hashmap;
};

static
inline int ftable_keycmpfunc(void *key1, void *key2)
{
  hex_func_id_t _key1 = DEREF_VOID(hex_func_id_t, key1);
  hex_func_id_t _key2 = DEREF_VOID(hex_func_id_t, key2);

  return _key1 == _key2;
}

static
inline int ftable_hashfunc(void *key)
{
  return (int)DEREF_VOID(hex_func_id_t, key);
}

Ftable ftable_create()
{
  Hashmap hashmap = hashmap_create(
    FTABLE_DEFAULT_CAPACITY,
    ftable_keycmpfunc,
    ftable_hashfunc
  );

  if(!hashmap) {
    errno = ENOMEM;
    return NULL;
  }

  Ftable ftable = HEX_MALLOC(struct HexFtable);

  if(!ftable) {
    errno = ENOMEM;
    return NULL;
  }

  return ftable;
}

FtableEntry ftable_create_entry(char *func_name,
  ParameterList params, hex_type_id_t return_type, TokenLoc token_loc)
{
  HEX_ASSERT(func_name);
  HEX_ASSERT(params);

  FtableEntry entry = HEX_MALLOC(struct HexFtableEntry);

  if(!entry) {
    errno = ENOMEM;
    return NULL;
  }

  entry->func_name = func_name;
  entry->params = params;
  entry->return_type = return_type;
  entry->token_loc = token_loc;
  entry->flags = 0;
}

size_t ftable_size(Ftable ftable)
{
  HEX_ASSERT(ftable);
  return hashmap_size(ftable->hashmap);
}

void* ftable_put(Ftable ftable, FtableEntry func)
{
  HEX_ASSERT(ftable);
  HEX_ASSERT(func);

  return hashmap_put(ftable->hashmap, func->func_id, func);
}

int ftable_remove(Ftbale ftable, hex_func_id_t func_id)
{
  HEX_ASSERT(ftable);
  return hashmap_remove_bucket(ftable->hashmap, func_id);
}

static
FtableEntry _ftable_lookup_by_id(void *key, void *value, void *arg)
{
  RETURN_VAL_IF_NULL(value, NULL);
  RETURN_VAL_IF_NULL(arg, NULL);

  hex_func_id_t lookup_id = (FtableLookupArg)arg;
  FtableEntry entry = (FtableEntry)value;

  return entry->func_id == arg->lookup_id ? entry : NULL; 
}

FtableEntry ftable_lookup_by_id(Ftable ftable, hex_func_id_t func_id)
{
  HEX_ASSERT(ftable);

  void *p = hashmap_lookup(ftable->hashmap, _ftable_lookup_by_id, &func_id);

  return (FtableEntry)p;
}

static
FtableEntry _ftable_lookup_by_name(void *key, void *val, void *arg)
{
  RETURN_VAL_IF_NULL(value, NULL);
  RETURN_VAL_IF_NULL(arg, NULL);

  char* lookup_name = (char*)arg;
  FtableEntry entry = (FtableEntry)value;

  return entry->func_name == lookup_name ? entry : NULL; 
}

FtableEntry ftable_lookup_by_name(Ftable ftable, char *lookup_name)
{
  HEX_ASSERT(ftable);

  void *p = hashmap_lookup(ftable->hashmap, _ftable_lookup_by_name, lookup_name);

  return (FtableEntry)p;
}

static
int _ftable_compare_params(ParameterList params1, ParameterList params2)
{
  RETURN_VAL_IF_TRUE(!params1 && !params2, 1);
  RETURN_VAL_IF_TRUE((!params1 && params2) || (params1 && !params2), NULL);

  while(param1 && param2) {
    Parameter p1 = param1->parameter;
    Parameter p2 = param2->parameter;

    RETURN_VAL_IF_TRUE(p1->type_id != p2->type_id, 0);

    param1 = param1->next;
    param2 = param2->next;
  }

  return 1;
}

FtableEntry ftable_lookup_by_signature(Ftable ftable, char *func_name, ParameterList params)
{
  HEX_ASSERT(ftable);

  FtableEntry existing_func = ftable_lookup_by_name(ftable, func_name);

  RETURN_VAL_IF_NULL(existing_func, NULL);

  return _ftable_compare_params(existing_func->params, params) ?
    existing_func : NULL;
}

size_t ftable_bucketcount(Ftable ftable)
{
  HEX_ASSERT(ftable);
  return hashmap_bucketcount(ftable->hashmap);
}

size_t ftable_capacity(Ftable ftable)
{
  HEX_ASSERT(ftable);
  return hashmap_capacity(ftable->hashmap);
}
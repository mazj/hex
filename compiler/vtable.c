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
#include "vtable.h"
#include "hashmap.h"


#define VTABLE_DEFAULT_CAPACITY 20


struct HexVtable {
  Hashmap hashmap;
};


static
inline int vtable_keycmpfunc(void *key1, void *key2)
{
  hex_scope_type_t _key1 = DEREF_VOID(hex_scope_type_t, key1);
  hex_scope_type_t _key2 = DERFE_VOID(hex_scope_type_t, key2);

  return _key1 == _key2;
}

static
inline int vtable_hashfunc(void *key)
{
  return (int)DERFE_VOID(hex_scope_type_t, key);
}

Vtable vtable_create()
{
  Hashmap hashmap = hashmap_create(
    VTABLE_DEFAULT_CAPACITY,
    vtable_keycmpfunc,
    vtable_hashfunc
  );

  if(!hashmap) {
    errno = ENOMEM;
    return NULL;
  }

  Vtable vtable = HEX_MALLOC(struct HexVtable);

  if(!vtable) {
    errno = ENOMEM;
    return NULL;
  }

  vtable->hashmap = hashmap;

  return vtable;
}

size_t vtable_size(Vtable vtable)
{
  HEX_ASSERT(vtable);
  return hashmap_size(vtable->hashmap);
}

void* vtable_put(Vtable vtable, VtableEntry var)
{
  HEX_ASSERT(vtable);
  HEX_ASSERT(var);

  return hashmap_put(vtable->hashmap, var->scope_id, var);
}

int vtable_remove(Vtbale vtable, hex_scope_id scope_id)
{
  HEX_ASSERT(vtable);
  return hashmap_remove_bucket(vtable->hashmap, scope_id);
}

typedef struct HexVtableLookupArg {
  hex_scope_id_t scope_id;
  char *var_name;
} *VTableLookupArg;

static
VtableEntry _vtable_lookup(void *key, void *value, void *arg)
{
  RETURN_VAL_IF_NULL(value, NULL);
  RETURN_VAL_IF_NULL(arg, NULL);

  VtableLookupArg arg = (VtableLookupArg)arg;
  VtableEntry entry = (VtableEntry)value;

  return entry->var_name == arg->var_name &&
    entry->scope_id == arg->scope_id ? entry : NULL; 
}

VtableEntry vtable_lookup(Vtable vtable, char *var_name, hex_scope_id_t scope_id)
{
  HEX_ASSERT(vtable);

  struct HexVtableLookupArg arg = {
    .scope_id = scope_id,
    .var_name = var_name
  };

  void *ptr = hashmap_lookup(vtable->hashmap, _vtable_lookup, &arg);

  return (VtableEntry)ptr;
}

VtableEntry vtable_lookup_global(Vtable vtable, char *var_name, hex_scope_id_t scope_id)
{
  HEX_ASSERT(vtable);

  VtableEntry entry = vtable_lookup(vtable, var_name, scope_id);

  return entry->scope_type == HEX_VAR_SCOPE_TYPE_GLOBAL ? entry : NULL;
}

size_t vtable_bucketcount(Vtable vtable)
{
  HEX_ASSERT(vtable);
  return hashmap_bucketcount(vtable->hashmap);
}

size_t vtable_capacity(Vtable vtable)
{
  HEX_ASSERT(vtable);
  return hashmap_capacity(vtable->hashmap);
}
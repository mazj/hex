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

#include <string.h>
#include <errno.h>
#include "../base/memory.h"
#include "../base/assert.h"
#include "../base/utils.h"
#include "../base/strbuf.h"
#include "../base/hashmap.h"
#include "vtable.h"


#define VTABLE_DEFAULT_CAPACITY 20


struct HexVtable {
  Hashmap hashmap;
};

/*
 * key is the mingled name of the variable.
 * hash is the hash of the mingled name.
 */

static
inline int _vtable_keycmpfunc(void *key1, void *key2)
{
  char* _key1 = (char*)key1; 
  char* _key2 = (char*)key2; 

  return strcmp(_key1, _key2) == 0;
}

static
inline int _vtable_hashfunc(void *key)
{
  return (hash_t)hash_str((char*)key);
}

/*
 * mingled name = 'name' + '_' + type + '_' + 'indent_level' + '_' + 'var_counter' 
 * */
char* vtable_mingle_name(VtableEntry entry)
{
  HEX_ASSERT(entry);
  HEX_ASSERT(entry->name);

  Strbuf strbuf = strbuf_create();
  HEX_ASSERT(strbuf);

  char type_str[2];
  char indent_level_str[5];
  char var_counter_str[5];
  
  snprintf(type_str, sizeof(type_str), "%u", (unsigned int)entry->type);
  snprintf(indent_level_str, sizeof(indent_level_str), "%u", entry->indent_level);
  snprintf(var_counter_str, sizeof(var_counter_str), "%u", entry->var_counter);

  strbuf_append(strbuf, (const char*)entry->name);
  strbuf_append(strbuf, "_");
  strbuf_append(strbuf, (const char*)type_str);
  strbuf_append(strbuf, "_");
  strbuf_append(strbuf, (const char*)indent_level_str);
  strbuf_append(strbuf, "_");
  strbuf_append(strbuf, (const char*)var_counter_str);

  char *mingled_name = strbuf_cstr(strbuf);

  HEX_ASSERT(mingled_name);

  HEX_FREE(strbuf);

  return mingled_name;
}

Vtable vtable_create()
{
  Hashmap hashmap = hashmap_create(
    VTABLE_DEFAULT_CAPACITY,
    _vtable_hashfunc,
    _vtable_keycmpfunc
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

size_t vtable_capacity(Vtable vtable)
{
  HEX_ASSERT(vtable);
  return hashmap_capacity(vtable->hashmap);
}

void* vtable_put(
  Vtable vtable,
  hex_scope_type_t scope_type,
  char *name,
  hex_type_t type,
  hex_type_qualifier_t type_qualifier,
  unsigned int indent_level,
  unsigned int var_counter)
{
  HEX_ASSERT(vtable);
  HEX_ASSERT(name);

  VtableEntry entry = HEX_MALLOC(struct HexVtableEntry);  
  RETURN_VAL_IF_NULL(entry, NULL);

  memset(entry, 0, sizeof(struct HexVtableEntry));

  entry->scope_type = scope_type;
  entry->name = name;
  entry->type = type;
  entry->type_qualifier = type_qualifier;
  entry->indent_level = indent_level;
  entry->var_counter = var_counter;

  entry->mingled_name = vtable_mingle_name(entry);

  return hashmap_put(vtable->hashmap, entry->mingled_name, entry);
}

typedef struct HexVtableLookupArg {
  char *name;
  unsigned int indent_level;
} *VtableLookupArg;

static
int _vtable_lookup(void *key, void *value, void *arg)
{
  HEX_ASSERT(value);
  HEX_ASSERT(arg);

  VtableLookupArg _arg = (VtableLookupArg)arg;
  VtableEntry _entry = (VtableEntry)value;

  return strcmp(_entry->name, _arg->name) == 0 &&
    _entry->indent_level == _arg->indent_level; 
}

VtableEntry vtable_lookup(Vtable vtable, char *name, unsigned int indent_level)
{
  HEX_ASSERT(vtable);
  HEX_ASSERT(name);

  struct HexVtableLookupArg arg = {
    .name = name,
    .indent_level = indent_level
  };

  VtableEntry entry = (VtableEntry)hashmap_lookup(vtable->hashmap, _vtable_lookup, &arg);

  return entry;
}

void vtable_free(Vtable *vtable)
{
  Vtable _vtable = *vtable;

  HEX_ASSERT(_vtable);

  hashmap_free(&_vtable->hashmap);

  HEX_FREE(_vtable);

  *vtable = _vtable;
}

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
#include "ftable.h"
#include "ttable.h"


#define TTABLE_DEFAULT_CAPACITY 20

struct HexTtableEntry {
  char *name;
  Vtable vtable;
  Ftable ftable;
};


struct HexTtable {
  Hashmap hashmap;
};


static
inline int _ttable_keycmpfunc(void *key1, void *key2)
{
  char *_key1 = (char*)key1;
  char *_key2 = (char*)key2;

  return strcmp(_key1, _key2) == 0;
}

static
inline int _ttable_hashfunc(void *key)
{
  return (hash_t)hash_str((char*)key);
}

Ttable ttable_create()
{
  Hashmap hashmap = hashmap_create(
    TTABLE_DEFAULT_CAPACITY,
    _ttable_hashfunc,
    _ttable_keycmpfunc
  );

  if(!hashmap) {
    errno = ENOMEM;
    return NULL;
  } 

  Ttable ttable = HEX_MALLOC(struct HexTtable);

  if(!ttable) {
    HEX_FREE(hashmap);
    errno = ENOMEM;
    return NULL;
  }

  ttable->hashmap = hashmap;

  return ttable;
}

static
TtableEntry _ttable_create_entry(char *name)
{
  HEX_ASSERT(name);

  Vtable _vtable = vtable_create();

  if(!_vtable) {
    errno = ENOMEM;
    return NULL;
  }

  Ftable _ftable = ftable_create();

  if(!_ftable) {
    HEX_FREE(_vtable);
    errno = ENOMEM;
    return NULL;
  }

  TtableEntry entry = HEX_MALLOC(struct HexTtableEntry);

  if(!entry) {
    HEX_FREE(_vtable);
    HEX_FREE(_ftable);
    errno = ENOMEM;
    return NULL;
  }

  char *_name = MALLOC(strlen(name)+1);

  if(!_name) {
    HEX_FREE(_vtable);
    HEX_FREE(_ftable);
    HEX_FREE(entry);
    errno = ENOMEM;
    return NULL;
  }

  entry->name = _name;
  entry->vtable = _vtable;
  entry->ftable = _ftable;

  strcpy(entry->name, name);

  return entry;
}

static
int _ttable_free_entry(void *name, void *entry)
{
  HEX_ASSERT(name);
  HEX_ASSERT(entry);

  char *_name = (char*)name;
  TtableEntry _entry = (TtableEntry)entry;

  vtable_free(&_entry->vtable);
  ftable_free(&_entry->ftable);

  HEX_ASSERT(_entry->vtable == NULL);
  HEX_ASSERT(_entry->ftable == NULL);

  return 1;
}

void ttable_free(Ttable *ttable)
{
  Ttable _ttable = *ttable;

  HEX_ASSERT(_ttable);

  hashmap_iterate(_ttable->hashmap, _ttable_free_entry, 0);
  hashmap_free(&_ttable->hashmap);

  HEX_ASSERT(_ttable->hashmap == NULL);

  HEX_FREE(_ttable);

  *ttable = _ttable;
}

size_t ttable_size(Ttable ttable)
{
  HEX_ASSERT(ttable);
  return hashmap_size(ttable->hashmap);
}

size_t ttable_capacity(Ttable ttable)
{
  HEX_ASSERT(ttable);
  return hashmap_capacity(ttable->hashmap);
}

void* ttable_put(
  Ttable ttable,
  char *name)
{
  HEX_ASSERT(ttable);
  HEX_ASSERT(name);

  TtableEntry _entry = _ttable_create_entry(name);

  HEX_ASSERT(_entry);

  return hashmap_put(ttable->hashmap, name, _entry); 
}

static
inline int _ttable_lookup(void *key, void *value, void *arg)
{
  HEX_ASSERT(key);
  HEX_ASSERT(arg);

  return strcmp((char*)key, (char*)arg) == 0;
}

TtableEntry ttable_lookup(Ttable ttable, char *name)
{
  HEX_ASSERT(ttable);
  HEX_ASSERT(name);

  return (TtableEntry)hashmap_lookup(ttable->hashmap, _ttable_lookup, name); 
}

void* ttable_put_member_var(
  Ttable ttable,
  char *name,
  char *member_name,
  hex_type_t type,
  hex_type_qualifier_t type_qualifier)
{
  HEX_ASSERT(ttable);
  HEX_ASSERT(name);
  HEX_ASSERT(member_name);

  TtableEntry entry = ttable_lookup(ttable, name);

  RETURN_VAL_IF_NULL(entry, NULL);

  return vtable_put(entry->vtable, HEX_VAR_SCOPE_TYPE_MEMBER,
    member_name, type, type_qualifier, 1); 
}

void* ttable_put_member_func(
  Ttable ttable,
  char *name,
  char *member_name,
  hex_type_t return_type,
  void* paramlist)
{
  HEX_ASSERT(ttable);
  HEX_ASSERT(name);
  HEX_ASSERT(member_name);

  TtableEntry entry = ttable_lookup(ttable, name);

  RETURN_VAL_IF_NULL(entry, NULL);

  return ftable_put(entry->ftable, member_name, return_type, paramlist);
}

int ttable_lookup_member_var(Ttable ttable, char *name, char *member_name)
{
  HEX_ASSERT(ttable);
  HEX_ASSERT(name);
  HEX_ASSERT(member_name);

  TtableEntry entry = ttable_lookup(ttable, name);

  RETURN_VAL_IF_NULL(entry, 0);

  void *p = vtable_lookup(entry->vtable, member_name, 1);

  return (p != NULL);
}

int ttable_lookup_member_func(Ttable ttable, char *name, char *member_name,
  void* paramlist)
{
  HEX_ASSERT(ttable);
  HEX_ASSERT(name);
  HEX_ASSERT(member_name);

  TtableEntry entry = ttable_lookup(ttable, name);

  RETURN_VAL_IF_NULL(entry, 0);

  void *p = ftable_lookup(entry->ftable, member_name, paramlist);

  return (p != NULL);
}

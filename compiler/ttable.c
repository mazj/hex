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
#include "ttable.h"
#include "hashmap.h"

#define TTABLE_DEFAULT_CAPACITY 20

struct HexTtable {
  Hashmap hashmap;
};

static
inline int _ttable_keycmpfunc(void *key1, void *key2)
{
  hex_type_id_t type1 = DEREF_VOID(hex_type_id_t key1);
  hex_type_id_t type2 = DEREF_VOID(hex_type_id_t key2);

  return type1 == type2;
}

static
inline int _ttable_hashfunc(void *key)
{
  return (int)DEREF_VOID(hex_type_id_t, key);
}

Ttable ttable_create()
{
  Hashmap hashmap = hashmap_create(
    TTABLE_DEFAULT_CAPACITY,
    ttable_keycmpfunc,
    ttable_hashfunc
  );

  if(!hashmap) {
    errno = ENOMEM;
    return NULL;
  }

  Ttable ttable = HEX_MALLOC(struct HexTtable);

  if(!ttable) {
    errno = ENOMEM;
    return NULL;
  }

  ttable->hashmap = hashmap;

  return ttable;
}

size_t ttable_size(Ttable ttable)
{
  HEX_ASSERT(ttable);
  return hashmap_size(ttable->hashmap);
}

void* ttable_put(Ttable ttable, TtableEntry entry)
{
  HEX_ASSERT(ttable);
  HEX_ASSERT(entry);

  return hashmap_put(ttable->hashmap, entry->type_id, entry);
}

int ttable_remove(Ttable ttable, hex_type_id_t type_id)
{
  HEX_ASSERT(ttable);

  return hashmap_remove_bucket(ttable, type_id);
}

static
TtableEntry _ttable_lookup(void *key, void *value, void *arg)
{
  RETURN_VAL_IF_NULL(key, NULL);
  RETURN_VAL_IF_NULL(value, NULL);

  hex_type_id_t type_id = DEREF_VOID(hex_type_id_t, arg);
  TtableEntry entry = (TtableEntry)value;

  return entry->type_id == type_id;
}

TtableEntry ttable_lookup(Ttable ttable, hex_type_id_t type_id)
{
  HEX_ASSERT(ttable);

  void *p = hashmap_lookup(ttable->hashmap, _ttable_lookup, &type_id);

  return (TtableEntry)p;
}

size_t ttable_bucketcount(Ttable ttable)
{
  HEX_ASSERT(ttable);
  return hashmap_bucketcount(ttable->hashmap);
}

size_t ttable_capacity(Ttable ttable)
{
  HEX_ASSERT(ttable);
  return hashmap_capacity(ttable->hashmap);
}

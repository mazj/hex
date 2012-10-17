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
#include "set.h"
#include "hashmap.h"

#define DEFAULT_SET_INITIAL_CAPACITY 10

struct HexSet_s {
  Hashmap _hashmap;
};

static
int set_keycmpfunc(void *key1, void *key2)
{
  int _key1 = *(int*)key1;
  int _key2 = *(int*)key2;

  return _key1 == _key2;
}

static
int set_hashfunc(void *key)
{
  return *(int*)key;
}

Set set_create()
{
  Set set = HEX_MALOOC(struct HexSet_s);

  if(set == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  Hashmap hashmap = hashmap_create(
    DEFAULT_SET_INITIAL_CAPACITY,
    set_hashfunc,
    set_keycmpfunc
  );

  if(hashmap == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  set->_hashmap = hashmap;

  return set;
}

int
set_empty(Set set)
{
  HEX_ASSERT(set);
  return hashmap_bucketcount(set->_hashmap) == 0;
}

static
int _set_contains(Set set, void *val)
{
  int *key = (int*)(*val);

  if(hashmap_contains_key(
    set->_hashmap,
    key,
    sizeof(int*))
  ) {
    return 0;
  }

  return 1;
}

int set_insert(Set set, void *val, size_t size)
{
  HEX_ASSERT(set);

  int *key = (int*)(*val);

  if(_set_contains(set, val)) {
    return 0;
  }

  return hashmap_put(set->_hashmap, key, val);
}

int set_contains(Set set, void *val)
{
  HEX_ASSERT(set);

  return _set_contains(set, val);
}

int set_equal(Set set1, Set set2)
{
  HEX_ASSERT(set1);
  HEX_ASSERT(set2);

  return hashmap_equal(set1->_hashmap, set2->_hashmap);
}

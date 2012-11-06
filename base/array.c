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

/*
 * Array abstraction
 */

#include <stddef.h>
#include <limits.h>
#include "memory.h"
#include "assert.h"
#include "array.h"
#include "utils.h"


#define INITIAL_CAPACITY 4
#define MAX_CAPACITY ((int)UINT_MAX/sizeof(void*))

struct HexArray_s {
  void** content;
  size_t size;
  size_t capacity;
};


Array
array_create()
{
  Array array = NULL;
  HEX_MALLOC_OR_ENOMEM(struct HexArray_s, array);
  return array;
}

void
array_free(Array array)
{
  HEX_ASSERT(array);
  HEX_FREE(array->content);
  HEX_FREE(array);
}

/*
 * Expand the capacity of the array, if the specified
 * capacity is greater than capacity of the array.
 */
static int
_ensure_capacity(Array array, size_t capacity)
{
  HEX_ASSERT(array);

  int oldCapacity = array->capacity;

  if(capacity > oldCapacity) {
    size_t newCapcity = (oldCapacity == 0) ?
      INITIAL_CAPACITY : oldCapacity;

    while(newCapcity < capacity) {
      int newCap = newCapcity * 2;
      if(newCap < newCapcity || newCap > MAX_CAPACITY) {
        newCap = MAX_CAPACITY;
      }
      newCapcity = newCap;
    }

    void **newContent=NULL;
    if(!array->content) {
      newContent = malloc(newCapcity * sizeof(void*));
      if(!newContent) {
        return -1;
      }
    } else {
      newContent = realloc(array->content, sizeof(void*) * newCapcity);
      if(!newContent) {
        return -1;
      }
    }

    array->capacity = newCapcity;
    array->content = newContent;
  }

  return 1;
}

int
array_append(Array array, void* ptr)
{
  HEX_ASSERT(array);

  size_t size = array->size;
  int res = _ensure_capacity(array, size+1);

  RETURN_VAL_IF_FALSE(res, res);

  array->content[size] = ptr;
  array->size++;

  return 1;
}

/*
 * Check the specified index is within the bound of the array.
 */
static
void _check_bound(Array array, int index)
{
  HEX_ASSERT(array);
  HEX_ASSERT(index >= 0 && index < array->size);
}

void*
array_remove(Array array, int index)
{
  HEX_ASSERT(array);

  _check_bound(array, index);

  void *ptr = array->content[index];

  int newSize = array->size - 1;

  if(index != newSize) {
    memmove(
      array->content+index,
      array->content+index+1,
      (sizeof(void*)) * (newSize - index)
    );
  }

  array->size = newSize;

  return ptr;
}

void*
array_set(Array array, int index, void* ptr)
{
  HEX_ASSERT(array);

  _check_bound(array, index);

  void* old = array->content[index];
  array->content[index] = ptr;

  return old;
}

int
array_set_size(Array array, int newSize)
{
  HEX_ASSERT(array);
  HEX_ASSERT(newSize >= 0);

  int oldSize = array->size;

  if(newSize > oldSize) {
    int res = _ensure_capacity(array, newSize);

    RETURN_VAL_IF_TRUE(res < 0, res);

    memset(
      array->content + sizeof(void*) * oldSize,
      0,
      sizeof(void*) * (newSize - oldSize)
    );

    array->size = newSize;

    return 1;
  }

  return 0;
}

int
array_size(Array array)
{
  HEX_ASSERT(array);
  return array->size;
}

const void**
array_content(Array array)
{
  HEX_ASSERT(array);
  return (const void**)array->content;
}
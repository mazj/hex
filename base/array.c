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
#include "utils.h"
#include "array.h"

#define DEFAULT_ARRAY_INITIAL_CAPACITY 4
#define ARRAY_MAX_CAPACITY ((int)UINT_MAX/sizeof(void*))


struct HexArray_s {
  void** content;
  size_t size;
  size_t capacity;
};

/*
 * Expand the capacity of the array, if the specified
 * capacity is greater than capacity of the array.
 */
static int
_array_ensure_capacity(Array array, size_t capacity)
{
  HEX_ASSERT(array);

  int oldCapacity = array->capacity;

  if(capacity > oldCapacity) {
    size_t newCapcity = (oldCapacity == 0) ?
      DEFAULT_ARRAY_INITIAL_CAPACITY : oldCapacity;

    while(newCapcity < capacity) {
      size_t newCap = newCapcity << 1;
      if(newCap < newCapcity || newCap > ARRAY_MAX_CAPACITY) {
        newCap = ARRAY_MAX_CAPACITY;
      }
      newCapcity = newCap;
    }

    void **newContent=NULL;
    if(!array->content) {
      newContent = malloc(newCapcity * sizeof(void*));
      if(!newContent) {
        errno = ENOMEM;
        return -1;
      }
    } else {
      newContent = realloc(array->content, sizeof(void*) * newCapcity);
      if(!newContent) {
        errno = ENOMEM;
        return -1;
      }
    }

    array->capacity = newCapcity;
    array->content = newContent;
  }

  return 1;
}

static
inline void _array_check_bound(Array array, int index)
{
  HEX_ASSERT(array);
  HEX_ASSERT(index >= 0 && index < array->size);
}

Array array_create()
{
  Array array = NULL;

  array = HEX_MALLOC(struct HexArray_s);

  if(!array) {
    errno = ENOMEM;
    return NULL;
  }

  array->content = NULL;
  array->size = 0;
  array->capacity = 0;

  _array_ensure_capacity(array, DEFAULT_ARRAY_INITIAL_CAPACITY);

  return array;
}

void array_free(Array *array)
{
  Array _array = *array;

  HEX_ASSERT(_array);
  HEX_FREE(_array->content);
  HEX_FREE(_array);

  *array = _array;
}

int
array_append(Array array, void* ptr)
{
  HEX_ASSERT(array);

  size_t size = array->size;
  int res = _array_ensure_capacity(array, size+1);

  RETURN_VAL_IF_FALSE(res, 0);

  array->content[size] = ptr;
  array->size++;

  return 1;
}

void*
array_get(Array array, int index)
{
  HEX_ASSERT(array);

  _array_check_bound(array, index);

  return array->content[index];
}

void*
array_remove(Array array, int index)
{
  HEX_ASSERT(array);

  _array_check_bound(array, index);

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

  _array_check_bound(array, index);

  void* old = array->content[index];
  array->content[index] = ptr;

  return old;
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

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

#include <stddef.h>
#include <stdio.h>
#include "assert.h"
#include "memory.h"
#include "utils.h"
#include "strbuf.h"


#define STRBUF_INITIAL_ALLOC 1024
static size_t strbuf_alloc_size = STRBUF_INITIAL_ALLOC;


struct HexStrbuf_s {
  char*  c_str;               /* pointer to the raw string */
  size_t  capacity;           /* size of allocated data */
  size_t  size;               /* amount of space used */
};


static
void init_strbuf(Strbuf strbuf, size_t min_len)
{
  RETURN_IF_NULL(strbuf);
  RETURN_IF_TRUE(strbuf->capacity > 0);

  char* d;

  if(min_len < strbuf_alloc_size) {
    min_len = strbuf_alloc_size;
  }

  d = (char*)malloc(min_len);

  if(!d) {
    errno = ENOMEM;
    exit(5);
  }

  strbuf->c_str = d;
  strbuf->capacity = min_len;
  strbuf->c_str[0] = 0;
  strbuf->size = 0;
}

/*
 * Make more room. Leaving contents unchanged, effectively.
 */
static
void _allocate_more(Strbuf strbuf, size_t len)
{
  RETURN_IF_NULL(strbuf);

  size_t new_capacity = strbuf->capacity + len;
  char* c_str = 0;

  if(new_capacity < strbuf_alloc_size) {
    new_capacity = strbuf_alloc_size;
  }

  c_str = realloc(strbuf->c_str, new_capacity);

  if(!c_str) {
    fprintf(stderr, "string buffer is out of memory re-allocating "
      "%lu bytes\n", (unsigned long)new_capacity);
    exit(-5);
  }

  strbuf->c_str = c_str;
  strbuf->capacity = new_capacity;
}

static
void _strbuf_appendn_internal(Strbuf strbuf, const char *in_str, size_t len);

void
strbuf_appendn(Strbuf strbuf, const char *in_str, size_t len)
{
  RETURN_IF_NULL(strbuf);
  RETURN_IF_NULL(in_str);

  size_t full_len = strlen(in_str);

  if(full_len < len) {
    fprintf(
      stderr,
      "esb internal error, bad string length %lu  < %lu \n",
      (unsigned long)full_len,
      (unsigned long)len
    );

    len = full_len;
  }

  _strbuf_appendn_internal(strbuf, in_str, len);
}

void
strbuf_append(Strbuf strbuf, const char *in_str)
{
  RETURN_IF_NULL(strbuf);
  RETURN_IF_NULL(in_str);

  size_t len = strlen(in_str);

  _strbuf_appendn_internal(strbuf, in_str, len);
}

static
void _strbuf_appendn_internal(Strbuf strbuf, const char *in_str, size_t len)
{
  size_t remaining = 0;
  size_t needed = len + 1;

  if(strbuf->capacity == 0) {
    size_t maxlen = (len > strbuf_alloc_size) ? len : strbuf_alloc_size;
    init_strbuf(strbuf, maxlen);
  }

  remaining = strbuf->capacity - strbuf->size;

  if(remaining < needed) {
    _allocate_more(strbuf, needed);
  }

  strncpy(&strbuf->c_str[strbuf->size], in_str, len);
  strbuf->size += len;

  /* Insist on explicit NUL terminator */
  strbuf->c_str[strbuf->size] = '\0';
}

char*
strbuf_get_string(Strbuf strbuf)
{
  HEX_ASSERT(strbuf);

  return strbuf->c_str;
}

void
strbuf_empty(Strbuf strbuf)
{
  RETURN_IF_NULL(strbuf);

  if(strbuf->capacity == 0) {
    init_strbuf(strbuf, strbuf_alloc_size);
  }

  strbuf->size = 0;
  strbuf->c_str[0] = 0;
}

size_t
strbuf_len(Strbuf strbuf)
{
  HEX_ASSERT(strbuf);
  return strbuf->size;
}

void
strbuf_constructor(Strbuf strbuf)
{
  HEX_ASSERT(strbuf);
  memset(strbuf, 0, sizeof(*strbuf));
}

void
strbuf_destructor(Strbuf strbuf)
{
  HEX_ASSERT(strbuf);

  if(strbuf->c_str) {
    HEX_FREE(strbuf->c_str);
    strbuf->size = 0;
    strbuf->capacity = 0;
  }
}

void
strbuf_reverse(Strbuf strbuf)
{
  RETURN_IF_NULL(strbuf);

  char *str = strbuf_get_string(strbuf);

  RETURN_IF_NULL(str);

  int i = 0;
  int j = strlen(str) - 1;

  while(i < j) {
    char tmp = str[i];
    str[i] = str[j];
    str[j] = tmp;
    i++;
    j--;
  }
}

void
strbuf_set_alloc_size(size_t size)
{
  strbuf_alloc_size = size;
}

size_t
strbuf_get_allocated_size(Strbuf strbuf)
{
  RETURN_IF_NULL(strbuf);
  return strbuf->capacity;
}

void
strbuf_append_printf(Strbuf strbuf, const char *in_str, ...)
{
  #define NULL_DEVICE_FILE "/dev/null"

  static FILE *null_file = NULL;

  int needed_size = 0;
  int length = 0;

  va_list ap;
  va_start(ap, in_str);

  if(null_file == NULL) {
    null_file = fopen(NULL_DEVICE_FILE, "w");
  }

  length = vfprintf(null_file, in_str, ap);

  /* Check if we require allocate more space */
  needed_size = strbuf->size + length;

  if(needed_size > strbuf->capacity) {
    _allocate_more(strbuf, length);
  }

  vsprintf(&strbuf->c_str[strbuf->size], in_str, ap);
  strbuf->size += length;
  va_end(ap);
}
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
#include <stdarg.h>
#include "assert.h"
#include "memory.h"
#include "utils.h"
#include "strbuf.h"


#define DEFAULT_STRBUF_INITIAL_ALLOC 1024

static const size_t _strbuf_alloc_size = DEFAULT_STRBUF_INITIAL_ALLOC;


struct HexStrbuf_s {
  char*  c_str;               /* pointer to the raw string */
  size_t  capacity;           /* size of allocated data */
  size_t  size;               /* amount of space used */
};


static
void _strbuf_init(Strbuf *strbuf, size_t min_len)
{
  Strbuf _strbuf = *strbuf;

  RETURN_IF_NULL(_strbuf);

  char* _str=NULL;

  size_t len = MAX(min_len, _strbuf_alloc_size);
  size_t capacity = len;

  _str = (char*)malloc(len);

  if(!_str) {
    errno = ENOMEM;
    exit(5);
  }

  memset(_str, 0, len);

  _strbuf->c_str = _str;
  _strbuf->size = 0;
  _strbuf->capacity = capacity;

  *strbuf = _strbuf;
}

static
void _strbuf_allocate_more(Strbuf *strbuf, size_t len)
{
  Strbuf _strbuf = *strbuf;

  HEX_ASSERT(_strbuf);

  size_t new_capacity = _strbuf->capacity + len;
  char* c_str = NULL;

  new_capacity = MAX(new_capacity, _strbuf_alloc_size);

  c_str = realloc(_strbuf->c_str, new_capacity);

  if(!c_str) {
    errno=ENOMEM;
    exit(-5);
  }

  _strbuf->c_str = c_str;
  _strbuf->capacity = new_capacity;

  *strbuf = _strbuf;
}

Strbuf strbuf_create()
{
  Strbuf strbuf=NULL;

  strbuf = HEX_MALLOC(struct HexStrbuf_s);

  if(!strbuf) {
    errno=ENOMEM;
    return NULL;
  }

  _strbuf_init(&strbuf, _strbuf_alloc_size);

  HEX_ASSERT(strbuf->c_str);
  return strbuf;
}

void
strbuf_free(Strbuf *strbuf)
{
  Strbuf _strbuf = *strbuf;

  HEX_ASSERT(_strbuf);

  char **_str = &_strbuf->c_str;
  
  HEX_FREE(*_str);
  _strbuf->size = 0;
  _strbuf->capacity = 0;

  HEX_FREE(_strbuf);

  *strbuf = _strbuf;
}

void
strbuf_empty(Strbuf strbuf)
{
  HEX_ASSERT(strbuf);

  HEX_FREE(strbuf->c_str);
  strbuf->size = 0;
  strbuf->capacity = 0;
  _strbuf_init(&strbuf, _strbuf_alloc_size);
}

size_t
strbuf_len(Strbuf strbuf)
{
  HEX_ASSERT(strbuf);
  return strbuf->size;
}

char*
strbuf_cstr(Strbuf strbuf)
{
  HEX_ASSERT(strbuf);
  return strbuf->c_str;
}

size_t
strbuf_capacity(Strbuf strbuf)
{
  HEX_ASSERT(strbuf);
  return strbuf->capacity;
}

int
strbuf_append(Strbuf strbuf, const char *in_str)
{
  HEX_ASSERT(strbuf);
  HEX_ASSERT(in_str);

  size_t len = strlen(in_str);
  size_t needed = len + 1;

  if(strbuf->capacity == 0) { 
    _strbuf_init(&strbuf, MAX(len, _strbuf_alloc_size));
  }

  if(len > strbuf->capacity) {
    _strbuf_allocate_more(&strbuf, needed);
  }
  strncpy(&strbuf->c_str[strbuf->size], in_str, len);
  strbuf->size += len;

  /* Insist on explicit NULL terminator */
  strbuf->c_str[strbuf->size] = '\0';

  return 1;
}

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
#include <stddef.h>
#include "memory.h"
#include "assert.h"
#include "buffer.h"
#include "utils.h"


typedef struct HexBuffer_s {
  char *data;                   /* byte array */
  union {
    size_t expected;            /* for reader, # of bytes expected */
    size_t remaining;           /* for writing, # of bytes remaining */
  };
  size_t size;                  /* actual size of buffer */
  size_t capacity;              /* amount of memory allocated for the buffer */
} *Buffer;


Buffer
buffer_create(size_t capacity)
{
  Buffer buffer = NULL;

  HEX_MALLOC_OR_ENOMEM(struct HexBuffer_s, buffer);

  RETURN_VAL_IF_NULL(buffer, NULL);

  buffer->data = malloc(capacity * sizeof(char));
  buffer->size = 0;
  buffer->capacity = capacity;
  buffer->expected = 0;

  FREE_IF_NULL(buffer->data, buffer);

  return buffer;
}

void
buffer_free(Buffer buffer)
{
  HEX_ASSERT(buffer);
  HEX_FREE(buffer->data);
  HEX_FREE(buffer);
}

Buffer
buffer_wrap(char *data, size_t capacity, size_t size)
{
  RETURN_VAL_IF_NULL(data, NULL);

  HEX_ASSERT(size <= capacity);

  Buffer buffer = NULL;

  HEX_MALLOC_OR_ENOMEM(struct HexBuffer_s, buffer);

  RETURN_VAL_IF_NULL(buffer, NULL);

  buffer->data = data;
  buffer->size = size;
  buffer->capacity = capacity;
  buffer->expected = 0;

  return buffer;
}

int
buffer_prepare_for_read(Buffer buffer, size_t expected)
{
  HEX_ASSERT(buffer);

  if(expected > buffer->expected) {
    char *expanded = realloc(buffer->data, expected);
    if(!expanded) {
      errno = ENOMEM;
      return -1;
    }
    buffer->capacity = expected;
    buffer->data = expanded;
  }

  buffer->expected = expected;

  return 1;
}

ssize_t
buffer_read(Buffer buffer, int fd)
{
  HEX_ASSERT(buffer);

  RETURN_VAL_IF_FALSE(buffer->size < buffer->expected, 0);

  ssize_t bytesRead = read(
    fd,
    buffer->data+buffer->size,
    buffer->expected-buffer->size
  );

  if(bytesRead > 0) {
    buffer->size += bytesRead;
    return buffer->size;
  }

  return bytesRead;
}

int
buffer_prepare_for_write(Buffer buffer)
{
  HEX_ASSERT(buffer);
  buffer->remaining = buffer->size;
}

ssize_t
buffer_write(Buffer buffer, int fd)
{
  HEX_ASSERT(buffer);

  RETURN_VAL_IF_FALSE(buffer->remaining > 0, 0);
  RETURN_VAL_IF_FALSE(buffer->remaining <= buffer->size, 0);

  ssize_t bytesWritten = write(
    fd,
    buffer->data+buffer->size-buffer->remaining,
    buffer->remaining
  );

  if(bytesWritten >= 0) {
    buffer->remaining -= bytesWritten;
    return buffer->remaining;
  }

  return bytesWritten;
}
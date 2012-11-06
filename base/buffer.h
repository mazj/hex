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

/* Buffer abstraction */

#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <stddef.h>
#include <stdlib.h>


/*
 * Byte buffer of known size. Keeps track of how much data has been read
 * into or written out of the buffer.
 */
typedef struct HexBuffer_s *Buffer;

/*
 * Returns true if all data has been read into the buffer.
 */
#define buffer_read_complete(buffer) ((buffer)->expected == (buffer)->size)

/*
 * Returns true if the buffer has been completely written.
 */
#define buffer_write_complete(buffer) ((buffer)->remaining == 0)

/*
 * Creates a new buffer with the given initial capacity.
 */
Buffer
buffer_create(size_t capacity);

/*
 * Frees the data in the buffer.
 */
void
buffer_free(Buffer buffer);

/*
 * Wraps an existing byte array.
 */
Buffer
buffer_wrap(char *data, size_t capacity, size_t size);

/*
 * Prepares buffer to read 'expected' number of bytes.
 * Expands capacity if necessary.
 */
int
buffer_prepare_for_read(Buffer buffer, size_t expected);

/*
 * Reads some data into a buffer. Returns -1 in case of an error and sets 
 * errno (see read()). Returns 0 for EOF. Updates buffer->size and returns
 * the new size after a succesful read. 
 *
 * Precondition: buffer->size <= buffer->expected
 */
ssize_t
buffer_read(Buffer buffer, int fd);

/*
 * Prepares a buffer to be written.
 */
int
buffer_prepare_for_write(Buffer buffer);

/*
 * Writes data from buffer to the given fd. Returns -1 and sets errno in case
 * of an error. Updates buffer->remaining and returns the number of remaining
 * bytes to be written after a successful write. 
 *
 * Precondition: buffer->remaining > 0
 */
ssize_t
buffer_write(Buffer buffer, int fd);


#endif /* _BUFFER_H_ */
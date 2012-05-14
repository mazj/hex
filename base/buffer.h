/* Buffer abstraction */

#ifndef _BUFFER_H_
#define _BUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

/*
 * Byte buffer of known size. Keeps track of how much data has been read
 * into or written out of the buffer.
 */
typedef struct HexBuffer_s {
	char *data;            /* byte array */
	union {
		size_t expected;   /* for reader, # of bytes expected */
		size_t remaining;  /* for writing, # of bytes remaining */
	}
	size_t size;           /* actual size of buffer */
	size_t capacity;       /* amount of memory allocated for the buffer */
} Buffer;

/*
 * Returns true if all data has been read into the buffer.
 */
#define bufferReadComplete(buffer) ((buffer)->expected == (buffer)->size)

/*
 * Returns true if the buffer has been completely written.
 */
#define bufferWriteComplete(buffer) ((buffer)->remaining == 0)

/*
 * Creates a new buffer with the given initial capacity.
 */
Buffer*
bufferCreate(size_t capacity);

/*
 * Wraps an existing byte array.
 */
Buffer*
bufferWrap(char* data, size_t capacity, size_t size);

/*
 * Frees the data in the buffer.
 */
void
bufferFree(Buffer *buffer);

/*
 * Prepares buffer to read 'expected' number of bytes.
 * Expands capacity if necessary.
 */
int
bufferPrepareForRead(Buffer *buffer, size_t expected);

/*
 * Reads some data into a buffer. Returns -1 in case of an error and sets 
 * errno (see read()). Returns 0 for EOF. Updates buffer->size and returns
 * the new size after a succesful read. 
 *
 * Precondition: buffer->size < buffer->expected
 */
ssize_t
bufferRead(Buffer *buffer, int fd);

/*
 * Prepares a buffer to be written.
 */
void
bufferPrepareForWrite(Buffer *buffer);

/*
 * Writes data from buffer to the given fd. Returns -1 and sets errno in case
 * of an error. Updates buffer->remaining and returns the number of remaining
 * bytes to be written after a successful write. 
 *
 * Precondition: buffer->remaining > 0
 */
ssize_t
bufferWrite(Buffer *buffer, int fd);

#ifdef __cplusplus
}
#endif

#endif /* _BUFFER_H_ */
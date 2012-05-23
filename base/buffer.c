#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "memory.h"
#include "assert.h"
#include "buffer.h"

Buffer*
bufferCreate(size_t capacity)
{
	Buffer *buffer = MALLOC(Buffer);
	if(!buffer) {
		return 0;
	}
	buffer->capacity = capacity;
	buffer->expected = 0;
	buffer->data = malloc(capacity * sizeof(char));
	if(!buffer->data) {
		free(buffer);
		return 0;
	}
	return buffer;
}

void
bufferFree(Buffer *buffer)
{
	HEX_ASSERT(buffer != NULL);
	free(buffer->data);
	free(buffer);
}

Buffer*
bufferWrap(char *data, size_t capacity, size_t size)
{
	Buffer *buffer = MALLOC(Buffer);
	if(!buffer) {
		return 0;
	}
	buffer->data = data;
	buffer->capacity = capacity;
	buffer->size = size;
	buffer->expected = 0;
	return buffer;
}

int
bufferPrepareForRead(Buffer *buffer, size_t expected)
{
	HEX_ASSERT(buffer != NULL);

	if(expected > buffer->expected) {
		char *expanded = realloc(buffer->data, expected);
		if(!expanded) {
			errno = ENOMEM;
			return -1;
		}
		buffer->capacity = expected;
		buffer->data = expanded;
	}

	buffer->size = 0;
	buffer->expected = expected;
	return 0;
}

ssize_t
bufferRead(Buffer *buffer, int fd)
{
	HEX_ASSERT(buffer != NULL);

	HEX_ASSERT(buffer->size < buffer->expected);

	ssize_t bytesRead = read(fd,
		buffer->data + buffer->size,
		buffer->expected - buffer->size);

	if(bytesRead > 0) {
		buffer->size += bytesRead;
		return buffer->size;
	}

	return bytesRead;
}

void
bufferPrepareForWrite(Buffer *buffer)
{
	buffer->remaining = buffer->size;
}

ssize_t
bufferWrite(Buffer *buffer, int fd)
{
	HEX_ASSERT(buffer->remaining > 0);
	HEX_ASSERT(buffer->remaining <= buffer->size);

	ssize_t bytesWritten = write(fd,
		buffer->data + buffer->size - buffer->remaining,
		buffer->remaining);

	if(bytesWritten >= 0) {
		buffer->remaining -= bytesWritten;
		return buffer->remaining;
	}

	return bytesWritten;
}
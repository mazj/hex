#ifndef BUFFER_H_
#define BUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

typedef struct HexBuffer_s {
	char *data;
	union {
		size_t expected;
		size_t remaining;
	}
	size_t size;
	size_t capacity;
} Buffer;

#define bufferReadComplete(buffer) ((buffer)->expected == (buffer)->size)

#define bufferWriteComplete(buffer) ((buffer)->remaining == 0)

Buffer* bufferCreate(size_t capacity);

Buffer* bufferWrap(char* data, size_t capacity, size_t size);

void
bufferFree(Buffer *buffer);

int
bufferPrepareForRead(Buffer *buffer, size_t expected);

ssize_t
bufferRead(Buffer *buffer, int fd);

void
bufferPrepareForWrite(Buffer *buffer);

ssize_t
bufferWrite(Buffer *buffer, int fd);

#ifdef __cplusplus
}
#endif

#endif /* BUFFER_H */
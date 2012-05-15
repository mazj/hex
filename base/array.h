/* Array abstraction */

#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <string.h>

typedef struct HexArray_s {
	void** content;
	size_t size;
	size_t capacity;
} Array;

Array*
arrayCreate();

void
arrayFree(Array *array);

static int
_ensure_capacity(Array* array, size_t capacity);

int
arrayAppend(Array *array, void* ptr);

static void
_check_bound(Array* array, int index);

void*
arrayRemove(Array *array, int index);

void*
arraySet(Array *array, int index, void* ptr);

int
arraySetSize(Array *array, int newSize);

int
arraySize(Array *array);

const void**
arrayContent(Array *array);

#endif /* _ARRAY_H_ */
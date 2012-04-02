#include <string.h>
#include <assert.h>

#define ARRAY_INITIAL_CAPACITY 4
#define ARRAY_MAX_CAPACITY     ((size_t)(UINT_MAX/sizeof(void*)))

struct Array {
	void** content;
	size_t size;
	size_t capacity;
};

Array*
array_createArray() {
	return (Array*)malloc(sizeof(Array));
}

void
array_freeArray(Array* array) {
	assert(array);
	free(array->content);
	free(array);
}

static int
_array_ensure_capacity(Array* array, size_t capacity) 
{
	size_t oldCapacity = array->capacity;
	if(capacity > oldCapacity) {
		size_t newCapacity = (oldCapacity == 0) ? ARRAY_INITIAL_CAPACITY : oldCapacity;

		if(capacity > ARRAY_MAX_CAPACITY)
			return -1;

		while(newCapacity < capacity) {
			size_t newCap = newCapacity * 2;

			if(newCap < newCapacity || newCap > ARRAY_MAX_CAPACITY)
				newCap = ARRAY_MAX_CAPACITY;

			newCapacity = newCap;
		}

		void** newContent;
		if(!array->content) {
			newContent = malloc(newCapacity * sizeof(void*));
			if(!newContent)
				return -1;
		} else {
			newContent = realloc(array->content, sizeof(void*) * newCapacity);
			if(!newContent)
				return -1;
		}

		array->capacity = newCapacity;
		array->content = newContent;
	}

	return 1;
}

int
array_insert(Array* array, void* ptr) {
	assert(array);
	size_t size = array->size;
	int res = _array_ensure_capacity(array, size+1);
	if(!res)
		return res;
	array->content[size] = ptr;
	array->size++;
	return 1;
}

static inline void
_array_check_bound(Array* array, size_t index) {
	assert(array);
	assert(index >= 0);
	assert(index < array->size);
}

void*
array_get(Array *array, size_t index) {
	_array_check_bound(array, index);
	return array->content[index];
}

void*
array_set(Array *array, size_t index, void* ptr) {
	_array_check_bound(array, index);
	void* oldPtr = array->content[index];
	array->content[index] = ptr;
	return oldPtr;
}

void*
array_remove(Array *array, size_t index) {
	_array_check_bound(array, index);

	void *ptr =array->content[index];

	int newSize = array->size - 1;

	if(index != newSize) {
		memmove(array->content + index, array->content + index + 1,
			(sizeof(void*)) * (newSize - index));
	}

	array->size = newSize;
	return ptr;
}

void*
array_set_size(Array *array, size_t newSize) {
	assert(array);
	assert(newSize >= 0);

	int oldSize = array->size;

	if(newSize > oldSize) {
		int res = _array_ensure_capacity(array, newSize);
		if(!res)
			return res;
	}

	memset(array->content + sizeof(void*) * oldSize, 0,
		sizeof(void*) * (newSize - oldSize));

	array->size = newSize;

	return 1;
}

int
array_size(Array *array) {
	assert(array);
	return array->size;
}

void**
array_get_content(Array *array) {
	return array->content;
}
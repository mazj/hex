#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <errno.h>

void
memset16(uint16_t *dst, uint16_t value, size_t size);


void
memset32(uint32_t *dst, uint32_t value, size_t size);


//===========================================================================
// convenience malloc macro.
// USE WITH CAUTION
//===========================================================================
#define MALLOC(T)					\
	(T*)malloc(sizeof(T))


//===========================================================================
// Convenience malloc macro.
// If malloc fails, set errno to ENOMEM and return null.
// USE WITH CAUTION
//===========================================================================
#define MALLOC_OR_ENOMEM(T, obj)		\
	(obj) = (T*)malloc(sizeof(T));		\
	do {								\
		if(obj == NULL) {				\
			errno = ENOMEM;				\
			return NULL;				\
		}								\
	} while(0)


//===========================================================================
// Derefernece a void* pointer to a data of specified type.
//
// T: The specified data type to be dereferenced.
// v: the value of type void*
//
// e.g.
// void deref_example(void* value) {
// 	  int i = *((int*)value);
// }
//
// can now be written as:
//
// void deref_example(void* value) {
// 	  int i = DEREF_VOID(int, value);
// }
//===========================================================================
#define DEREF_VOID(T, v)	\
	*( (T*)( (v) ) );


#ifndef /* _MEMORY_H_ */
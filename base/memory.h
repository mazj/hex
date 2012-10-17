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

#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <stdint.h>
#include <string.h>
#include <errno.h>


void memset16(uint16_t *dst, uint16_t value, size_t size);
void memset32(uint32_t *dst, uint32_t value, size_t size);


//===========================================================================
// convenience malloc macro.
// USE WITH CAUTION
//===========================================================================
#define MALLOC(size_)                    \
  malloc( (size_) )


//===========================================================================
// convenience malloc macro.
// USE WITH CAUTION
//===========================================================================
#define HEX_MALLOC(T)                    \
  (T*)malloc(sizeof(T))


//===========================================================================
// Convenience malloc macro.
// If malloc fails, set errno to ENOMEM and return null.
// USE WITH CAUTION
//===========================================================================
#define HEX_MALLOC_OR_ENOMEM(T, obj)     \
  (obj) = (T*)malloc(sizeof(T));         \
  do {                                   \
    if((obj) == NULL) {                  \
      errno = ENOMEM;                    \
    }                                    \
  } while(0)


//===========================================================================
// Derefernece a void* pointer to a data of specified type.
//
// T: The specified data type to be dereferenced.
// v: the value of type void*
//
// e.g.
// void deref_example(void* value) {
//   int i = *((int*)value);
// }
//
// can now be written as:
//
// void deref_example(void* value) {
//   int i = DEREF_VOID(int, value);
// }
//
// USE WITH CAUTION
//===========================================================================
#define DEREF_VOID(T, v)                 \
  *( (T*)( (v) ) );


//===========================================================================
// Free-up memory.
// USE WITH CAUTION
//===========================================================================
#define HEX_FREE(x)                      \
  do {                                   \
    if( (x) ) {                          \
      free( (x) );                       \
      (x) = NULL;                        \
    }                                    \
  } while(0)


//===========================================================================
// Free target if val is null.
// USE WITH CAUTION
//===========================================================================
#define FREE_IF_NULL(val, target)        \
  do {                                   \
    if( (val) == NULL) {                 \
      HEX_FREE( (target) );              \
    }                                    \
  } while(0)


#endif /* _MEMORY_H_ */
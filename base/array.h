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

/* Array abstraction */

#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <stddef.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef struct HexArray_s *Array;

Array array_create();

void array_free(Array *array);

int array_append(Array array, void* ptr);

void* array_get(Array array, int index);

void* array_remove(Array array, int index);

void* array_set(Array array, int index, void* ptr);

int array_size(Array array);

const void** array_content(Array array);


#ifdef __cplusplus
}
#endif

#endif /* _ARRAY_H_ */

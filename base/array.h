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


typedef struct HexArray_s *Array;

Array
array_create();

void
array_free(Array array);

/*
 * Append the specified item to the end of the array.
 */
int
array_append(Array array, void* ptr);

/*
 * Remove an item in the array at the specified index, if found.
 * Returns the removed item.
 */
void*
array_remove(Array array, int index);

void*
array_set(Array array, int index, void* ptr);

int
array_set_size(Array array, int newSize);

int
array_size(Array array);

const void**
array_content(Array array);


#endif /* _ARRAY_H_ */
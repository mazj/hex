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

/* A container that holds a unique set of elements. */

#ifndef _SET_H_
#define _SET_H_

#include <stddef.h>


typedef struct HexSet_s *Set;

Set set_create();

int set_empty(Set set);

int set_insert(Set set, void *val, size_t size);

int set_contains(Set set, void *val);

int set_equal(Set set1, Set set2);


#endif /* _SET_H_ */
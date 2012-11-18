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

/* Binary search tree abstraction */

#ifndef _BST_H_
#define _BST_H_

#include <stddef.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct HexBst_s *Bst;

//===========================================================================
// A generic comparing function that compares the value of arg1 and arg2.
// Returns:
//    0: if both values are the same
//    1: if arg1 is less than arg2
//   -1: if arg1 is greater than arg2 
//===========================================================================
typedef int (*CmpFunc) (void *arg1, void *arg2);

Bst bst_create();

void bst_free(Bst *bst);

size_t bst_size(Bst bst);

size_t bst_height(Bst bst);

int bst_equal(Bst bst1, Bst bst2, CmpFunc);

void* bst_front(Bst bst);

void* bst_back(Bst bst);

int bst_insert(Bst bst, void *val, size_t size, CmpFunc);

void* bst_find(Bst bst, void *val, CmpFunc);


#ifdef __cplusplus
}
#endif

#endif /* _BST_H_ */

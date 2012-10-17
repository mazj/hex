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

/* Stack - FILO container */

#ifndef _STACK_H_
#define _STACK_H_

#include <stddef.h>

typedef struct HexStack_s *Stack;


Stack create_stack();

size_t stack_size(Stack stack);

void* stack_top(Stack stack);

int stack_push(Stack stack, void *val, size_t size);

void* stack_pop(Stack stack);


#endif /* _STACK_H_ */
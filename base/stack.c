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

#include <errno.h>
#include "assert.h"
#include "memory.h"
#include "utils.h"
#include "stack.h"


struct HexStack_s {
  Node top;
  size_t size;
};


Stack stack_create()
{
  Stack stack = HEX_MALLOC(struct HexStack_s);

  if(stack == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  stack->top = NULL;
  stack->size = 0;

  return stack;
}

size_t stack_size(Stack stack)
{
  HEX_ASSERT(stack);
  return stack->size;
}

void* stack_top(Stack stack)
{
  HEX_ASSERT(stack);
  RETURN_VAL_IF_NULL(stack->top, NULL);
  return stack->top->value;
}

int stack_push(Stack stack, void *val, size_t size)
{
  HEX_ASSERT(stack);

  RETURN_VAL_IF_NULL(val, 0);

  Node node = HEX_MALLOC(struct HexNode_s);

  if(!node) {
    errno = ENOMEM;
    return -1;
  }

  memset(node, 0, sizeof(struct HexNode_s));

  node->value = MALLOC(size);
  RETURN_VAL_IF_NULL(node->value, -1);

  memcpy(node->value, val, size);
  node->next = NULL;

  if(stack->top) {
    node->next = stack->top;
  }

  stack->top = node;
  stack->size++;

  return 1;
}

void* stack_pop(Stack stack) 
{
  HEX_ASSERT(stack);

  RETURN_VAL_IF_NULL(stack->top, NULL);

  Node top = stack->top;

  HEX_ASSERT(top);
  stack->top = top->next;

  void* val = top->value;

  HEX_FREE(top);
  stack->size--;

  return val;
}

void stack_free(Stack *stack)
{
  Stack _stack = *stack;
  HEX_ASSERT(_stack);

  while(stack_size(_stack) > 0) {
    stack_pop(_stack);
  }

  HEX_ASSERT(_stack->top == NULL);
  HEX_ASSERT(_stack->size == 0);

  HEX_FREE(_stack);

  *stack = _stack;
}

/* Stack - FILO container */

#ifndef _STACK_H_
#define _STACK_H_

#include <stdlib.h>
#include "utils.h"

typedef struct {
	Node* top;
	size_t size;
} Stack;

size_t
stack_size(Stack *s);

void*
stack_top(Stack *s);

void
stack_push(Stack *s, void* value);

void*
stack_pop(Stack* s);

#endif /* _STACK_H_ */
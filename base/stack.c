#include <assert.h>
#include "stack.h"

size_t
stack_size(Stack *s)
{
	assert(s != NULL);
	return s->size;
}

void*
stack_top(Stack *s)
{
	assert(s != NULL);
	if(s->top) {
		return s->top->value;
	} else {
		return 0;
	}
}

void
stack_push(Stack *s, void* value)
{
	assert(s != NULL);
	Node* node = MALLOC(Node);
	node->value = value;
	if(s->top) node->next = s->top;
	s->top = node;
	s->size++;
}

void*
stack_pop(Stack* s) 
{
	assert(s != NULL);
	assert(s->top != NULL);
	Node* node = s->top;
	s->top = s->top->next;
	if(node) {
		void* value = node->value;
		free(node);
		s->size--;
		return value;
	}
	return 0;
}
/* Stack - FILO container */
#ifndef _STACK_H_
#define _STACK_H_

#include "utils.h"

typedef struct {
	Node* top;
	int size;
} Stack;

int stack_size(Stack *s) {
	return s ? s->size : 0;
}

void* stack_top(Stack *s) {
	return (s && s->top) ? s->top->value : 0; 
}

void stack_push(Stack *s, void* value) {
	if(!s) return;
	Node* node = (Node*)malloc(sizeof(Node));
	node->value = value;
	if(s->top) node->next = s->top;
	s->top = node;
	s->size++;
}

void* stack_pop(Stack* s) {
	if(!s || !s->top) return 0;
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

#endif // _STACK_H_
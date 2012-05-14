#include <errno.h>
#include <assert.h>
#include "queue.h"

Queue*
createQueue()
{
	Queue* q = MALLOC(Queue);
	if(!q) {
		errno = ENOMEM;
		return 0;
	}
	q->front = 0;
	q->back = 0;
	q->size = 0;
	return q;
}

size_t
queue_size(Queue *q)
{
	assert(q != NULL);
	return q->size;
}

void*
queue_front(Queue *q)
{
	assert(q != NULL);
	assert(q->front != NULL);
	return q->front->value;
}

void*
queue_back(Queue *q)
{
	assert(q != NULL);
	assert(q->back != NULL);
	return q->back->value;
}

void
queue_push(Queue* q, void* value)
{
	assert(q != NULL);
	DoubleNode* node = MALLOC(DoubleNode);
	node->value = value;
	node->next = q->back;
	node->previous = 0;
	if(!q->back) q->back = MALLOC(DoubleNode);
	q->back->previous = node;
	q->back = node;
	q->size++;
	if(q->size == 1) q->front = node;
}

void*
queue_pop(Queue* q)
{
	assert(q != NULL);
	if(q->size == 0) return 0;
	DoubleNode* front = q->front;
	if(front->previous) {
		((DoubleNode*)(front->previous))->next = 0;
		q->front = front->previous;
	} else { // has only one node
		q->front = 0;
		q->back = 0;
	}
	q->size--;
	return front->value;
}
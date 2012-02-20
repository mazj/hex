/* Queue - FIFO storage container. */
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "utils.h"

typedef struct {
	DoubleNode* front;
	DoubleNode* back;
	int size;	
} Queue;

/* Gets the size of the queue. */
#define QUEUE_SIZE(q) (q) ? (q)->size : 0
int queue_size(Queue* q) {
	return q ? q->size : 0;
}

/* Gets the value at the front of the queue. */
#define QUEUE_FRONT(q) (q)->front ? (q)->front->value : 0
void* queue_front(Queue* q) {
	return (q && q->front) ? q->front->value : 0;
}

/* Gets the value at the back of the queue. */
#define QUEUE_BACK(q) ((q) && (q)->back) ? (q)->back->value : 0;
void* queue_back(Queue* q) {
	return (q && q->back) ? q->back->value : 0;
}

/* Pushes the value at the front of the queue. */
#define QUEUE_PUSH(q, value)										\
	if(!(q)) return;												\
	DoubleNode* node = (DoubleNode*)malloc(sizeof(DoubleNode));		\
	memset(node->value, value, sizeof(*(value));					\
	node->next = (q)->back;											\
	node->back = 0;													\
	(q)->back->previous = node;										\
	(q)->back = node;												\
	(q)->size++;

void queue_push(Queue* q, void* value) {
	if(!q) return;
	DoubleNode* node = (DoubleNode*)malloc(sizeof(DoubleNode));
	memset(node->value, value, sizeof(*value));
	node->next = q->back;
	node->previous = 0;
	q->back->previous = node;
	q->back = node;
	q->size++;
}

/* Returns the value at the front of the queue. */
void* queue_pop(Queue* q) {
	if(!q || !q->size) return 0;
	DoubleNode* front = q->front;
	if(front->previous) {
		((DoubleNode*)(front->previous))->next = 0;
		q->front = front->previous;
	} else { // has only one node
		q->front = 0;
	}
	q->size--;
	return front->value;
}

#endif // _QUEUE_H_
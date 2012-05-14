/* Queue - FIFO storage container. */

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "utils.h"

typedef struct {
	DoubleNode* front;
	DoubleNode* back;
	size_t size;	
} Queue;


Queue*
createQueue();

size_t
queue_size(Queue* q);

void*
queue_front(Queue* q);

void*
queue_back(Queue* q);

void
queue_push(Queue* q, void* value);

void*
queue_pop(Queue* q);

#endif /* _QUEUE_H_ */
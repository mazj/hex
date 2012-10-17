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
#include "queue.h"


struct HexQueue_s {
  Node head;      /* pop at head */
  Node tail;      /* push at tail */
  size_t size;
};


Queue create_queue()
{
  Queue queue = HEX_MALLOC(struct HexQueue_s);

  if(queue == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  queue->head = NULL;
  queue->tail = NULL;
  queue->size = 0;

  return queue;
}

size_t queue_size(Queue queue)
{
  HEX_ASSERT(queue);
  return queue->size;
}

void* queue_front(Queue queue)
{
  HEX_ASSERT(queue);
  RETURN_VAL_IF_NULL(queue->head, NULL);
  return queue->head->value;
}

void* queue_back(Queue queue)
{
  HEX_ASSERT(queue);
  RETURN_VAL_IF_NULL(queue->tail, NULL);
  return queue->tail->value;
}

int queue_push(Queue queue, void *val, size_t size)
{
  HEX_ASSERT(queue);

  RETURN_VAL_IF_NULL(val, 0);

  Node node = HEX_MALLOC(struct HexNode_s);

  if(!node) {
    errno = ENOMEM;
    return -1;
  }

  if(!node->value) {
    node->value = MALLOC(size);
    RETURN_VAL_IF_NULL(node->value, -1);
  }

  memcpy(node->value, val, size);
  node->next = NULL;

  if(queue->tail) {
    queue->tail->next = node;
  }
  queue->tail = node;

  if(queue->size == 0) {
    queue->head = queue->tail;
  }

  return 1;
}

void* queue_pop(Queue queue)
{
  HEX_ASSERT(queue);

  RETURN_VAL_IF_EQUALS(queue->size, 0, NULL);

  HEX_ASSERT(queue->head);

  void *val = queue->head->value;

  Node next = queue->head->next;

  HEX_FREE(queue->head);
  queue->size--;

  if(queue->size == 0) {
    queue->tail = NULL;
    HEX_ASSERT(queue->head == NULL);
  }

  return val;
}
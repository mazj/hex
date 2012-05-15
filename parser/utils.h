/* Common utilities. */

#ifndef _UTILS_H_
#define _UTILS_H_

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))


//===========================================================================
// Singly linked list node.
//===========================================================================
#ifndef _NODE_H_
typedef struct hex_node_s {
	void* value;
	struct hex_node_s* next;
} node_s;
#endif // _NODE_H_


//===========================================================================
// Doubly linked list node.
//===========================================================================
#ifndef _DOUBLE_NODE_H_
typedef struct {
	void* value;
	struct DoubleNode* next;
	struct DoubleNode* previous;
} DoubleNode;
#endif // _DOUBLE_NODE_H_


#endif // _UTILS_H_
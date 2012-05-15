/* Common utilities. */

#ifndef _UTILS_H_
#define _UTILS_H_

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))


//===========================================================================
// Singly linked list node.
//===========================================================================
typedef struct HexNode_s {
	void* value;
	struct HexNode_s* next;
} Node;


//===========================================================================
// Doubly linked list node.
//===========================================================================
typedef struct HexDoubleNode_s {
	void* value;
	struct HexDoubleNode_s* next;
	struct HexDoubleNode_s* previous;
} DoubleNode;


typedef struct HexBinaryNode_s {
	struct HexBinaryNode_s* left;
	struct HexBinaryNode_s* right;
	void* value;
} BinaryNode;

#endif /* _UTILS_H_ */
/* Common utilities. */

#ifndef _UTILS_H_
#define _UTILS_H_

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))


//===========================================================================
// Singly linked list node.
//===========================================================================
#ifndef _NODE_H_
typedef struct {
	void* value;
	struct Node* next;
} Node;
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


//===========================================================================
// malloc
//===========================================================================
#define MALLOC(T)					\
	(T*)malloc(sizeof(T))


//===========================================================================
// Derefernece a void* pointer to a data of specified type.
//
// T: The specified data type to be dereferenced.
// v: the value of type void*
//
// e.g.
// void deref_example(void* value) {
// 	  int i = *((int*)value);
// }
//
// can now be written as:
//
// void deref_example(void* value) {
// 	  int i = DEREF_VOID(int, value);
// }
//===========================================================================
#define DEREF_VOID(T, v)	\
	*( (T*)( (v) ) );

#endif // _UTILS_H_
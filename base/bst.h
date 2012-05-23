/* Binary search tree. */

#ifndef _BST_H_
#define _BST_H_

#include <stdlib.h>
#include "utils.h"

typedef struct HexBst_s {
	BinaryNode *root;
	size_t height;
} Bst;

//===========================================================================
// A generic comparing function that compares the value of arg1 and arg2.
// Returns:
// 			0: if both values are the same
//		    1: if arg1 is less than arg2
//         -1: if arg1 is greater than arg2 
//===========================================================================
typedef int (*CmpFunc) (void* arg1, void* arg2);

Bst*
createBst();

static inline
BinaryNode* bst_left(BinaryNode* node);

static inline
BinaryNode* bst_right(BinaryNode* node);

static BinaryNode*
bstCreateNode();

void*
bst_node_value(BinaryNode* node);

int
bst_node_isleafnode(BinaryNode* node);

int
bst_node_isfullnode(BinaryNode* node);

int
bst_node_empty(BinaryNode* node);

size_t
bst_size(Bst *bst);

size_t
bst_height(Bst *bst);

int
bst_equal(BinaryNode *node1, BinaryNode *node2, CmpFunc);

void*
bst_front(Bst *bst);

void*
bst_back(Bst *bst);

void*
bst_node_front(BinaryNode *node);

void*
bst_node_back(BinaryNode *node);

BinaryNode*
bst_node_insert(BinaryNode *node, void *val, size_t size, CmpFunc);

BinaryNode*
bst_node_find(BinaryNode *node, void *val, CmpFunc);

/* Generates a list of all the values in ascending order. */
Node*
bst_to_list(Bst *bst);

#endif /* _BST_H_ */
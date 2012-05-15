/* Binary search tree. */

#ifndef _BST_H_
#define _BST_H_

#include <stdlib.h>
#include "utils.h"

typedef struct {
	struct BinaryNode* left;
	struct BinaryNode* right;
	void* value;
} BinaryNode;

typedef struct HexBst_s {
	BinaryNode *root;
	size_t height;
} Bst;

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

int
bst_height(Bst *bst);

void*
bst_front(Bst *bst);

void*
bst_back(Bst *bst);

void*
bst_node_front(BinaryNode *node);

void*
bst_node_back(BinaryNode *node);

/* Generates a list of all the values in ascending order. */
Node*
bst_to_list(Bst *bst);

#endif /* _BST_H_ */
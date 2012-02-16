/* Binary search tree. */
#ifndef _BST_H_
#define _BST_H_

#include "utils.h"

typedef struct {
	struct BinaryNode* left;
	struct BinaryNode* right;
	void* value;
} BinaryNode;

#define BST_LEFT(x) (x) ? (BinaryNode*)(x)->left : 0
#define BST_RIGHT(x) (x) ? (BinaryNode*)(x)->right : 0

BinaryNode* bst_left(BinaryNode* node) {
	return node ? node->left : 0;
}

BinaryNode* bst_right(BinaryNode* node) {
	return node ? node->right : 0;
}

BinaryNode* bst_create_node() {
	return (BinaryNode*)malloc(sizeof(BinaryNode));
}

void* bst_value(BinaryNode* node) {
	return node ? node->value : 0;
}

/* Determines if the given node is a leaf node. */
int bst_isleafnode(const BinaryNode* node) {
	return !node || (!node->left && !node->right);
}

/* Determines if the given node is a full node(has two children). */
int bst_isfullnode(const BinaryNode* node) {
	return node && node->left && node->right;
}

/* Determines if the given node is empty. */
int bst_empty(const BinaryNode* node) {
	return node == 0 || (!node->left && !node->right);
}

/* Gets the size of the subtree starting with the given node. */
int bst_size(const BinaryNode* node) {
	return (node == 0) ? 0 : 1 + bst_size(node->left) + bst_size(node->right);
}

/* Gets the height of the subtree starting with the given node. */
int bst_height(const BinaryNode* node) {
	return (node == 0) ? -1 : MAX(1 + bst_height(node->left), 1 + bst_height(node->right));
}

/* Gets the front of the subtree starting with the give node. */
void* bst_front(const BinaryNode* node) {
	if(!node || !node->value) return 0;
	return (node->left == 0) ? node->value : bst_front(node->left) ? bst_front(node->left) : node->value;
}

/* Gets the back of the subtree starting with the given node. */
void* bst_back(const BinaryNode* node) {
	if(!node || !node->value) return 0;
	return (node->right == 0) ? node->value : bst_back(node->right) ? bst_back(node->right) : node->value;
}

#endif // _BST_H_
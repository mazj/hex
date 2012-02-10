/* Binary search tree. */
#ifndef BST_H
#define BST_H

#include "utils.h"

typedef struct {
	void* left;
	void* right;
	void* value;
} BinaryNode;

/* Determines if the given node is a leaf node. */
int bst_isleaf(const BinaryNode* node) {
	return !node || (!node->left && !node->right);
}

/* Determines if the given node is a full node(has two children). */
int bst_isfullnode(const BinaryNode* node) {
	return node && node->left && node->right;
}

/* Determines if the given node is empty. */
int bst_empty(const BinaryNode* node) {
	return node == 0;
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
	return (node->left == 0) ? node->value : bst_front(node->left);
}

/* Gets the back of the subtree starting with the given node. */
void* bst_back(const BinaryNode* node) {
	return (node->right == 0) ? node->value : bst_back(node->right);
}


#endif // BST_H
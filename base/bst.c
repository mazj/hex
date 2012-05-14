#include <assert.h>
#include <errno.h>
#include "bst.h"

Bst*
createBst()
{
	Bst *bst = MALLOC(Bst);
	if(bst == NULL) {
		errno = ENOMEM;
		return 0;
	}
	bst->height = 1;
	bst->root = 0;
	return bst;
}

static inline 
BinaryNode* bst_left(BinaryNode* node)
{
	assert(node != NULL);
	return node->left;
}

static inline
BinaryNode* bst_right(BinaryNode* node)
{
	assert(node != NULL);
	return node->right;
}

static BinaryNode*
bstCreateNode()
{
	BinaryNode *node = MALLOC(sizeof(BinaryNode));
	if(!node) {
		errno = ENOMEM;
		return 0;
	}
	return node;
}

void*
bst_node_value(BinaryNode* node)
{
	assert(node != NULL);
	return node->value;
}

int
bst_node_isleafnode(BinaryNode* node)
{
	assert(node != NULL);
	return (!node->left && !node->right);
}

int
bst_node_isfullnode(BinaryNode* node)
{
	assert(node != NULL);
	return (node->left && node->right);
}

int
bst_node_empty(BinaryNode* node)
{
	return node == 0 || (!node->left && !node->right);
}

/* Gets the size of the subtree starting with the given node. */
static size_t
_bst_size(BinaryNode* node)
{
	return (node == 0) ? 0 : 1 + _bst_size(node->left) + _bst_size(node->right);
}

int
bst_size(Bst *bst)
{
	assert(bst != NULL);
	if(!bst->root) {
		return 0;
	}
	return _bst_size(bst->root);
}

static size_t
_bst_height(BinaryNode* node)
{
	return (node == 0) ? -1 : MAX(1 + _bst_height(node->left),
		1 + _bst_height(node->right));
}

size_t
bst_height(Bst *bst)
{
	assert(bst != NULL);
	if(!bst->root) {
		return 0;
	}
	return _bst_height(bst->root);
}

static void*
_bst_front(BinaryNode* node)
{
	if(!node || !node->value) return 0;
	return (node->left == 0) ? node->value : _bst_front(node->left) ? _bst_front(node->left) : node->value;
}

void*
bst_front(Bst *bst)
{
	assert(bst != NULL);
	return _bst_front(bst->root);
}

static void*
_bst_back(BinaryNode* node)
{
	if(!node || !node->value) return 0;
	return (node->right == 0) ? node->value :
		_bst_back(node->right) ? _bst_back(node->right) : node->value;
}

void*
bst_back(Bst *bst)
{
	assert(bst != NULL);
	return _bst_back(bst->root);
}

static void
_bst_append_to_list(BinaryNode* node, Node** list) {
    if(!node) return;
    _bst_append_to_list(node->right, list);
    if(node) {
        Node* tmp = MALLOC(Node);
        tmp->value = node->value; //memset(tmp->value, list->value, sizeof(list->value));
        tmp->next = *list;
        *list = tmp;
    }
    _bst_append_to_list(node->left, list);
}

Node*
bst_to_list(Bst *bst)
{
	assert(bst != NULL);
    Node* list = 0;
    _bst_append_to_list(node, &list);
    return list;
}
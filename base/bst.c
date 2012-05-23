#include <errno.h>
#include "assert.h"
#include "memory.h"
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

static BinaryNode*
bst_left(BinaryNode* node)
{
	HEX_ASSERT(node != NULL);
	return node->left;
}

static BinaryNode*
bst_right(BinaryNode* node)
{
	HEX_ASSERT(node != NULL);
	return node->right;
}

static BinaryNode*
bstCreateNode()
{
	BinaryNode *node = MALLOC(BinaryNode);
	if(!node) {
		errno = ENOMEM;
		return 0;
	}
	return node;
}

void*
bst_node_value(BinaryNode* node)
{
	HEX_ASSERT(node != NULL);
	return node->value;
}

int
bst_node_isleafnode(BinaryNode* node)
{
	HEX_ASSERT(node != NULL);
	return (!node->left && !node->right);
}

int
bst_node_isfullnode(BinaryNode* node)
{
	HEX_ASSERT(node != NULL);
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
	return (node == 0) ? 0 :
		1 + _bst_size(node->left) 
		+ _bst_size(node->right);
}

size_t
bst_size(Bst *bst)
{
	HEX_ASSERT(bst != NULL);
	if(!bst->root) {
		return 0;
	}
	return _bst_size(bst->root);
}

static size_t
_bst_height(BinaryNode* node)
{
	return (node == 0) ? -1 :
		MAX(1 + _bst_height(node->left),
		1 + _bst_height(node->right));
}

size_t
bst_height(Bst *bst)
{
	HEX_ASSERT(bst != NULL);
	if(!bst->root) {
		return 0;
	}
	return _bst_height(bst->root);
}

int
bst_equal(BinaryNode *node1, BinaryNode *node2,
	CmpFunc cmpfunc)
{
	if(node1 && node2) {
		if(cmpfunc(node1->value, node2->value) == 0) {
			return (bst_equal(
				node1->left, node2->left, cmpfunc) &&
				bst_equal(
					node1->right, node2->right, cmpfunc));
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}


static void*
_bst_front(BinaryNode* node)
{
	if(!node || !node->value) return 0;
	return (node->left == 0) ? node->value :
		_bst_front(node->left) ? 
		_bst_front(node->left) : node->value;
}

void*
bst_front(Bst *bst)
{
	HEX_ASSERT(bst != NULL);
	return _bst_front(bst->root);
}

void*
bst_node_front(BinaryNode *node)
{
	return _bst_front(node);
}

static void*
_bst_back(BinaryNode* node)
{
	if(!node || !node->value) return 0;
	return (node->right == 0) ? node->value :
		_bst_back(node->right) ? 
		_bst_back(node->right) : node->value;
}

void*
bst_back(Bst *bst)
{
	HEX_ASSERT(bst != NULL);
	return _bst_back(bst->root);
}

void*
bst_node_back(BinaryNode *node)
{
	return _bst_back(node);
}

static void
_bst_append_to_list(BinaryNode* node, Node** list) {
    if(!node) return;
    _bst_append_to_list(node->right, list);
    if(node) {
        Node* tmp = MALLOC(Node);
        tmp->value = node->value;
        tmp->next = *list;
        *list = tmp;
    }
    _bst_append_to_list(node->left, list);
}

Node*
bst_to_list(Bst *bst)
{
	HEX_ASSERT(bst != NULL);
    Node* list = 0;
    _bst_append_to_list(bst->root, &list);
    return list;
}

BinaryNode*
bst_node_insert(BinaryNode *node, void *val,
	size_t size, CmpFunc cmpfunc)
{
	if(node == NULL) {
		return NULL;
	}

	HEX_ASSERT(val != NULL);

	if(node->value == NULL || 
		cmpfunc(node->value, val) == 0) {
		memcpy(node->value, val, size);
		return node;
	} else if(cmpfunc(node->value, val) < 0) {
		return bst_node_insert(
			node->left, val, size, cmpfunc);
	} else {
		return bst_node_insert(
			node->right, val, size, cmpfunc);
	}
}

BinaryNode*
bst_node_find(BinaryNode *node, void *val, CmpFunc cmpfunc)
{
	if(node == NULL) {
		return NULL;
	}

	if(cmpfunc(node->value, val) == 0) {
		return node;
	} else if(cmpfunc(node->value, val) < 0) {
		return bst_node_find(node->left, val, cmpfunc);
	} else {
		return bst_node_find(node->right, val, cmpfunc);
	}
}
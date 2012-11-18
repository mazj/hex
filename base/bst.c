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
#include "bst.h"

struct HexBst_s {
  BinaryNode root;
};


Bst bst_create()
{
  Bst bst = HEX_MALLOC(struct HexBst_s);

  if(bst == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  bst->root = NULL;

  return bst;
}

static
inline void _bst_free_node(BinaryNode node)
{
  RETURN_IF_NULL(node);

  _bst_free_node(node->left);
  _bst_free_node(node->right);

  node->left = NULL;
  node->right = NULL;

  HEX_FREE(node->value);
  HEX_FREE(node);
}

void bst_free(Bst *bst)
{
  Bst _bst = *bst;

  HEX_ASSERT(_bst);

  _bst_free_node(_bst->root);

  HEX_FREE(_bst);

  *bst = _bst;
}

static
inline BinaryNode _bst_left(BinaryNode node)
{
  RETURN_VAL_IF_NULL(node, NULL);
  return node->left;
}

static
inline BinaryNode _bst_right(BinaryNode node)
{
  RETURN_VAL_IF_NULL(node, NULL);
  return node->right;
}

static
inline BinaryNode _bst_create_node(size_t size)
{
  BinaryNode node = NULL;
  void *val = NULL;

  node = HEX_MALLOC(struct HexBinaryNode_s);

  if(!node) {
    errno = ENOMEM;
    return NULL;
  }

  val = MALLOC(size);

  if(!node->value) {
    errno = ENOMEM;
    HEX_FREE(node);
    return NULL;
  }

  node->left = NULL;
  node->right = NULL;
  node->value = val; 

  return node;
}

static
inline void* _bst_node_value(BinaryNode node)
{
  RETURN_VAL_IF_NULL(node, NULL);
  return node->value;
}

static
inline int _bst_node_isleafnode(BinaryNode node)
{
  RETURN_VAL_IF_NULL(node, 0);
  return (!node->left && !node->right);
}

static
inline int _bst_node_isfullnode(BinaryNode node)
{
  RETURN_VAL_IF_NULL(node, 0);
  return (node->left && node->right);
}

static
inline int _bst_node_empty(BinaryNode node)
{
  return node == NULL || (!node->left && !node->right);
}

/* Gets the size of the subtree starting with the given node. */
static
inline size_t _bst_size(BinaryNode node)
{
  return (node == NULL) ? 0 :
    1 + _bst_size(node->left) 
    + _bst_size(node->right);
}

size_t
bst_size(Bst bst)
{
  HEX_ASSERT(bst);
  return bst->root ? _bst_size(bst->root) : 0;
}

static
inline size_t _bst_height(BinaryNode node)
{
  return (node == NULL) ? -1 : 1+
    MAX(
      _bst_height(node->left),
      _bst_height(node->right)
    );
}

size_t
bst_height(Bst bst)
{
  HEX_ASSERT(bst);
  return bst->root ? _bst_height(bst->root) : 0;
}

static
int _bst_equal(BinaryNode node1, BinaryNode node2, CmpFunc cmpfunc)
{
  if(node1 && node2) {
    if(cmpfunc(node1->value, node2->value) == 0) {
      return (
        _bst_equal(
          node1->left,
          node2->left,
          cmpfunc
        ) &&
      	_bst_equal(
          node1->right,
          node2->right,
          cmpfunc
        )
      );
    } else {
      return 0;
    }
  } else {
    return 0;
  }
}

int
bst_equal(Bst bst1, Bst bst2, CmpFunc cmpfunc)
{
  HEX_ASSERT(bst1);
  HEX_ASSERT(bst2);
  return _bst_equal(bst1->root, bst2->root, cmpfunc);
}

static
inline void* _bst_front(BinaryNode node)
{
  HEX_ASSERT(node);
  return node->left == 0 ? node->value : _bst_front(node->left);
}

void*
bst_front(Bst bst)
{
  HEX_ASSERT(bst);
  return _bst_front(bst->root);
}

static
inline void* _bst_back(BinaryNode node)
{
  HEX_ASSERT(node);
  return (node->right == 0) ? node->value : _bst_back(node->right);
}

void*
bst_back(Bst bst)
{
  HEX_ASSERT(bst);
  return _bst_back(bst->root);
}

static
int _bst_insert(BinaryNode node, void *val, size_t size, CmpFunc cmpfunc)
{
  int res = cmpfunc(node->value, val);

  if(res < 0) {
    if(!node->left) {
      node->left = _bst_create_node(size);
      memcpy(node->left->value, val, size);
      return 1;
    } else {
      return _bst_insert(node->left, val, size, cmpfunc);
    }
  } else if(res > 0) {
    if(!node->right) {
      node->right = _bst_create_node(size);
      memcpy(node->right->value, val, size);
      return 1;
    } else {
      return _bst_insert(node->right, val, size, cmpfunc);
    }
  }

  return 0;
}

int
bst_insert(Bst bst, void *val, size_t size, CmpFunc cmpfunc)
{
  HEX_ASSERT(bst);
  HEX_ASSERT(val);

  if(!bst->root) {
    bst->root = _bst_create_node(size);
    memcpy(bst->root->value, val, size);
    return 1;
  }

  return _bst_insert(bst->root, val, size, cmpfunc);
}

static
inline void* _bst_find(BinaryNode node, void *val, CmpFunc cmpfunc)
{
  RETURN_VAL_IF_NULL(node, NULL);

  int res = cmpfunc(node->value, val);

  if(res < 0) {
    return _bst_find(node->left, val, cmpfunc);
  } else if(res > 0) {
    return _bst_find(node->right, val, cmpfunc);
  }

  return node->value;
}

void*
bst_find(Bst bst, void *val, CmpFunc cmpfunc)
{
  HEX_ASSERT(bst);
  HEX_ASSERT(val);

  return _bst_find(bst->root, val, cmpfunc);
}

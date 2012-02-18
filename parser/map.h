/* key-value pair map. */

#ifndef _MAP_H_
#define _MAP_H_

#include <stdio.h>
#include "bst.h"

// Defines a generic key-value pair.
typedef struct KVpair {
	void* key;
	void* value;
} Pair;


//===========================================================================
// A generic comparing function that compares the value of arg1 and arg2.
// Returns:
// 			0: if both values are the same
//		    1: if arg1 is less than arg2
//         -1: if arg1 is greater than arg2 
//===========================================================================
typedef int (*CmpFunc) (void* arg1, void* arg2);

BinaryNode* map_insert(BinaryNode* node, Pair* pair, CmpFunc* cmpfunc) {
    if(!node) {
        node = (BinaryNode*)malloc(sizeof(BinaryNode));
        node->value = pair;
        return node;
    }
    else if(!node->value) {
        node->value = pair;
        return node;
    } else {
    	int i = (*cmpfunc)(((Pair*)(node->value))->key, pair->key);
        if(i == 0) return node;
        if(i > 0) {
            BinaryNode* n = map_insert(node->left, pair, cmpfunc);
            if(n && !node->left) {
                node->left = n;
            }
            return n;
        }
        if(i < 0) {
            BinaryNode* n = map_insert(node->right, pair, cmpfunc);
            if(n && !node->right) {
                node->right = n;
            }
            return n;
        }
    }
}

/* Find the value that corresponds to the given key. 
   Returns 0 if not found. */
void* map_find(BinaryNode* node, const void* key, CmpFunc cmpfunc) {
    if(!node || !node->value) return 0;
	int i = (*cmpfunc)(((Pair*)(node->value))->key, key);
	if(i == 0) return node;
	if(i > 0) return map_find(node->left, key, cmpfunc);
	if(i < 0) return stl_find(node->right, key, cmpfunc);
}

/* Removes the node in the container that has the same value as
   the given value. Returns true if successful, false otherwise. */
int map_remove(BinaryNode* node, BinaryNode* ptr_to_node, const void* value, CmpFunc cmpfunc) {
	void* v= ((Pair*)(node->value))->value;
	if(!node || !ptr_to_node) return 0;
	int i = (*cmpfunc)(v, value);
	if(i==0) {
		if(bst_isleafnode(node)) { // leaf node
			ptr_to_node = 0;
			free(node);
		} else if(bst_isfullnode(node)) { // full node
			void* nextGreaterValue = bst_front(node->right);
			memcpy(v, nextGreaterValue, sizeof(*nextGreaterValue));
            map_remove(node->right, node, v, cmpfunc);
        } else { // only one child node
            if(node->left) ptr_to_node = node->left;
            else ptr_to_node = node->right;
            free(node);
        }
        return 1;
	} else if(i == -1) {
        if(!node->left) return 0;
        else return map_remove(node->left, node, value, cmpfunc);
    } else {
        if(!node->right) return 0;
        else return map_remove(node->right, node, value, cmpfunc);
    }
}

#endif // _MAP_H_
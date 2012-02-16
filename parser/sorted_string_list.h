/* Sorted string list. */
#ifndef _SORTED_STRING_LIST_
#define _SORTED_STRING_LIST_

#include "strnutils.h"
#include "bst.h"


BinaryNode* stl_insert(BinaryNode* node, const char* value) {
    if(!node) {
        node = (BinaryNode*)malloc(sizeof(BinaryNode));
        node->value = malloc(sizeof(strlen(value)));
        strcpy((char*)node->value, value);
        return node;
    }
    else if(!node->value) {
        node->value = malloc(sizeof(strlen(value)));
        strcpy((char*)(node->value), value);
        return node;
    } else {
        int i = strcmp((char*)(node->value), value);
        if(i == 0) return node;
        if(i > 0) {
            BinaryNode* n = stl_insert(node->left, value);
            if(n) {
                node->left = n;
                return n;
            }
        }
        if(i < 0) {
            BinaryNode* n = stl_insert(node->right, value);
            if(n) {
                node->right = n;
                return n;
            }
        }
    }
}

/* Insert node2 as a child node of node1.
 * If node1 is null, the make node2 the parent.
 * Returns the parent node. */
BinaryNode* stl_insert_node(BinaryNode* node1, BinaryNode* node2) {
    if(!node1 || !node2) return 0;

    int i = strcmp((char*)(node1->value), (char*)(node2->value));
    if(i == 0) {
        strcpy_hard((char*)(node1->value), (const char*)(node2->value));
        return node1;
    }
    if(i > 0) return stl_insert_node(node1->left, node2);
    if(i < 0) return stl_insert_node(node1->right, node2);
}

/* Find the specified string value among the given node
 * and all of its descendents. If found, return the pointer
 * to the child node that contains the identical string,
 * otherwise returns null. */
BinaryNode* stl_find(BinaryNode* node, const char* value) {
    if(!node || !node->value) return 0;
	int i = strcmp((char*)(node->value), value);
	if(i == 0) return node;
	if(i > 0) return stl_find(node->left, value);
	if(i < 0) return stl_find(node->right, value);
}


/* Remove a child node of the given node that contains
 * the same string as the given value. Returns true if
 * success, false otherwise. */
int stl_remove(BinaryNode* node, BinaryNode* ptr_to_node, const char* value) {
    if(!node || !ptr_to_node) return 0;
	if(strcmp((char*)node->value, value)==0) {
		if(bst_isleafnode(node)) { // leaf node
			ptr_to_node = 0;
			free(node);
		} else if(bst_isfullnode(node)) { // full node
            strcpy_hard((char*)node->value, (char*)bst_front(node->right));
            stl_remove(node->right, node, node->value);
        } else { // only one child node
            if(node->left) ptr_to_node = node->left;
            else ptr_to_node = node->right;
            free(node);
        }
        return 1;
	} else if(strcmp((char*)node->value, value) == -1) {
        if(!node->left) return 0;
        else return stl_remove(node->left, node, value);
    } else {
        if(!node->right) return 0;
        else return stl_remove(node->right, node, value);
    }
}

#endif // _SORTED_STRING_LIST_
/* Sorted string list. */

#include "strutils.h"
#include "bst.h"

/*  */
void stl_insert(BinaryNode* node1, BinaryNode* node2) {
	if(!node1) {
		node1 = (BinaryNode*)malloc(sizeof(BinaryNode));
		strcpy_hard((char*)(node1->value), (const char*)(node2->value));
	}
	int i = strcmp((char*)(node1->value), (char*)(node2->value));
	if(i == 0) strcpy_hard((char*)(node1->value), (const char*)(node2->value));
	if(i < 0) stl_insert(node1->left, node2);
	if(i > 0) stl_insert(node1->right, node2);
}

/* Find the specified string value among the given node
 * and all of its descendents. If found, return the pointer
 * to the child node that contains the identical string,
 * otherwise returns null. */
BinaryNode* stl_find(BinaryNode* node, const char* value) {
	int i = strcmp((char*)(node->value), value);
	if(i == 0) return node;
	if(i < 0) return stl_find(node->left, value);
	if(i > 0) return stl_find(node->right, value);
}


/* Remove a child node of the given node that contains
 * the same string as the given value. Returns true if
 * success, false otherwise. */
int stl_remove(BinaryNode* node, BinaryNode* ptr_to_node, const char* value) {
	if(strcmp((char*)node->value, value)==0) {
		if(bst_isleaf(node)) { // leaf node
			ptr_to_node = 0;
			free(node);
		} else if(bst_isfullnode(node)) { // full node
            strcpy_hard(node->value, bst_front(node->right));
            stl_remove(node->value, node->right);
        } else { // only one child node
            if(node->left) ptr_to_node = node->left;
            else ptr_to_node = node->right;
            free(node);
        }
        return true;
	} else if(strcmp((char*)node->value, value) == -1) {
        if(!node->left) return 0;
        else return stl_remove(node, node->left, value);
    } else {
        if(!node->right) return 0;
        else return stl_remove(node, node->right, value);
    }
}







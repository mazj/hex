/* Sorted string list. */

#ifndef _SORTED_STRING_LIST_
#define _SORTED_STRING_LIST_


BinaryNode*
stl_insert(BinaryNode* node, const char* value);

/*
 * Insert node2 as a child node of node1.
 * If node1 is null, the make node2 the parent.
 * Returns the parent node.
 */
BinaryNode*
stl_insert_node(BinaryNode* node1, BinaryNode* node2);

/*
 * Find the specified string value among the given node
 * and all of its descendents. If found, return the pointer
 * to the child node that contains the identical string,
 * otherwise returns null.
 */
BinaryNode*
stl_find(BinaryNode* node, const char* value);

/*
 * Remove a child node of the given node that contains
 * the same string as the given value. Returns true if
 * success, false otherwise.
 */
int
stl_remove(BinaryNode* node, BinaryNode* ptr_to_node,
    const char* value);


#endif // _SORTED_STRING_LIST_
/* key-value pair map. */

#ifndef _MAP_H_
#define _MAP_H_

#include <stdio.h>
#include "bst.h"

typedef struct HexMap_s {
    BinaryNode* root;
    size_t size;  
} Map;

//===========================================================================
// A generic comparing function that compares the value of arg1 and arg2.
// Returns:
// 			0: if both values are the same
//		    1: if arg1 is less than arg2
//         -1: if arg1 is greater than arg2 
//===========================================================================
typedef int (*CmpFunc) (void* arg1, void* arg2);

Map*
createMap();

size_t
map_size(Map* map);

BinaryNode*
map_head(Map* map);

BinaryNode*
map_insert(Map* map, void* key, void* value, CmpFunc cmpfunc);

void*
map_find(Map* map, const void* key, CmpFunc cmpfunc);


/* 
 * Removes the node in the container that has
 * the same value as the given value.
 * Returns true if successful, false otherwise.
 */
int
map_remove(BinaryNode* node, BinaryNode* ptr_to_node,
    const void* value, CmpFunc cmpfunc);

#endif /* _MAP_H_ */
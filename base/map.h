/* key-value pair map. */

#ifndef _MAP_H_
#define _MAP_H_

#include <stdio.h>
#include "bst.h"

typedef struct HexMap_s {
    BinaryNode* root;
    size_t size;  
} Map;

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
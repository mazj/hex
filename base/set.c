#include "set.h"
#include "bst.h"
#include "memory.h"
#include "assert.h"

struct HexSet_s {
	BinaryNode *root;
	CmpFunc cmpfunc;
	size_t size;
};

Set*
create_set()
{
	Set *set = MALLOC(Set);
	return set;
}

int
set_empty(Set *set)
{
	HEX_ASSERT(set != NULL);
	return set->size == 0;
}

BinaryNode*
set_insert(Set *set, void *val, size_t size)
{
	HEX_ASSERT(set != NULL);
	bst_node_insert(set->root, val, size, set->cmpfunc);
}

BinaryNode*
set_find(Set *set, void *val)
{
	HEX_ASSERT(set != NULL);
	return bst_node_find(set->root, val, set->cmpfunc);
}

int
set_equal(Set *s1, Set *s2)
{
	HEX_ASSERT(s1 != NULL);
	HEX_ASSERT(s2 != NULL);

	return bst_equal(s1->root, s2->root, s1->cmpfunc);
}
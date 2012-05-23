/* A container that holds a unique set of elements. */

#ifndef _SET_H_
#define _SET_H_

#include <stdlib.h>
#include "utils.h"

typedef struct HexSet_s Set;

Set*
create_set();

int
set_empty(Set *set);

BinaryNode*
set_insert(Set *set, void *val, size_t size);

BinaryNode*
set_find(Set *set, void *val);

int
set_equal(Set *s1, Set *s2);

#endif /* _SET_H_ */
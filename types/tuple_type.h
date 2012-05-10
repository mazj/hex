#ifndef HEX_TUPLE_OBJ_H
#define HEX_TUPLE_OBJ_H

#include "hex.h"
#include "object.h"

#ifdef __cplusplus
extern "C" {
#endif


/* Hex tuple object type. */
typedef struct HexTupleObj_s {
  HexObject *obj_items[1];
} HexTupleObj;

/* Convenience macros(use with caution). */
#define HexTuple_GET_ITEM(obj, i) (((HexTupleObj*)(obj))->obj_items[(i)])
#define HexTuple_SET_ITEM(obj, i, val) (((HexTupleObj*)(obj))->obj_items[(i)] = (val))

HexObject* HexTuple_Alloc(Hex_size_t);
HexObject* HexTuple_Size(HexObject*);
HexObject* HexTuple_GetItem(HexObject*, Hex_size_t);
int HexTuple_SetItem(HexObject*, Hex_size_t, HexObject*);


#ifdef __cplusplus
}
#endif

#endif /* HEX_TUPLE_OBJ_H */
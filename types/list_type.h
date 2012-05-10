/*
 * HEX list object type.
 */

#ifndef HEX_LIST_OBJ_H
#define HEX_LIST_OBJ_H

#include "hex.h"
#include "object.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * List object interface
 */
typedef struct HexListObj_s {
  HexObject **obj_list;
  Hex_size_t size; 
} HexListObj;


/* Convenience macros(use with caution). */
#define HexList_GET_ITEM(obj, i) (((HexListObj*)(obj))->obj_list[(i)])
#define HexList_SET_ITEM(obj, i, val) (((HexListObj*)(obj))->obj_list[(i)] = (val))
#define HexList_GET_SIZE(obj) (((HexListObj*)(obj))->size)

/*
 * Allocate a new instance of HexListObj
 */
HexObject* HexList_Alloc(Hex_size_t);


/*
 * Get the size of a HexListObj
 */
Hex_size_t HexList_Size(HexObject*);


/*
 * Get the list of items in HexListObj.
 */
HexObject** HexList_Items(HexObject*);


/*
 * Get a particular item of objects in HexListObj
 */
HexObject* HexList_GetItem(HexObject*, Hex_index_t);


/*
 *  Set a particular item in HexListObj.
 */
int HexList_SetItem(HexObject*, Hex_index_t, HexObject*);


/*
 * Insert a particular item in HexListObj.
 */
int HexList_Insert(HexObject*, Hex_index_t, HexObject*);


/*
 * Append an item to HexListObj.
 */
int HexList_Append(HexObject*, Hex_index_t, HexObject*);


/*
 * Sort the items in HexListObj.
 */
int HexList_Sort(HexObject*);


/*
 * Reverse the order of items in HexObjList.
 */
int HexList_Reverse(HexObject*);


/*
 * Convert a HexListObj to HexTupleObj.
 */
int HexList_AsTuple(HexObject*);


/*
 * Extend a HexListObj.
 */
int HexListObj_Extend(HexObject*, HexListObj*);


#ifdef __cplusplus
}
#endif

#endif /* HEX_LIST_OBJ_H */
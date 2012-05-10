#ifndef HEX_CLASS_OBJ_H
#define HEX_CLASS_OBJ_H

#include "hex.h"
#include "object.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _HexClassObj_s {
  HexObject *cls_bases;
  HexObject *cls_name;
} HexClassObj;

typedef struct _HexInstanceObj_s {
  HexClassObj *inst_class;
} HexInstanceObj;

typedef struct _HexMethodObj_s {
  HexObject* meth_class;
  HexObject *meth_func;
} HexMethodObj;


/* Convenience macros(use with caution). */
#define HexClass_Check(obj)  ((obj)->obj_type == &HexClass_Type)
#define HexInstance_Check(obj) ((obj)->obj_type == &HexInstance_Type)
#define HexMethod_Check(obj) ((obj)->obj_type == &HexMethod_Type)


HexObject* HexClass_Alloc(HexObject*);
HexObject* HexInstance_Alloc(HexObject*);
HexObject* HexMethod_Alloc(HexObject*);


#ifdef __cplusplus
}
#endif

#endif /* HEX_CLASS_OBJ_H */
/* HEX class type */

#ifndef _HEX_CLASS_OBJ_H_
#define _HEX_CLASS_OBJ_H_

#include "object.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct HexClassObj_s {
  HexObject *cls_bases;
  HexObject *cls_interfaces;
  HexObject *cls_name;
  HexObject *cls_attributes;
  HexObject *cls_constructor;
  HexObject *cls_destructor;
  HexObject *cls_members;
  HexObject *cls_methods;
  HexObject *cls_static_members;
  HexObject *cls_static_methods;
  struct HexObject_s *next;
} HexClassObj;


typedef struct HexInstanceObj_s {
  HexClassObj *inst_class;
  HexObject *inst_name;
} HexInstanceObj;


typedef struct HexMethodObj_s {
  HexObject *metd_name;
  HexObject* metd_class;
  HexObject *metd_func;
  HexObject *metd_parameters;
  HexObject *metd_returnval;
  HexObject *metd_is_virtual;
  HexObject *metd_is_extension;
} HexMethodObj;


/* Convenience macros(use with caution). */
#define HexClass_Check(obj)  ((obj)->obj_type == HexClass_Type)
#define HexInstance_Check(obj) ((obj)->obj_type == HexInstance_Type)
#define HexMethod_Check(obj) ((obj)->obj_type == HexMethod_Type)


HexObject*
HexClass_New(HexObject* cls_bases,
	HexObject *cls_interfaces, HexObject *cls_name,
	HexObject *cls_attributes, HexObject *cls_constructor,
	HexObject *cls_destructor, HexObject *cls_members,
	HexObject *cls_methods, HexObject *cls_static_members,
	HexObject *cls_static_methods);


HexObject*
HexInstance_New(HexObject *inst_class, HexObject *inst_name);


HexObject*
HexMethod_New(HexObject *metd_name, HexObject* metd_class,
	HexObject *metd_func, HexObject *metd_parameters,
	HexObject *metd_returnval, HexObject *metd_is_virtual,
	HexObject *metd_is_extension);


#ifdef __cplusplus
}
#endif

#endif /* _HEX_CLASS_OBJ_H_ */
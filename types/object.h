#ifndef _HEX_OBJECT_H_
#define _HEX_OBJECT_H_

#include "hex.h"

#ifdef _cplusplus
extern "C" {
#endif

/*
 * HexObject constructor and destructor. 
 */
typedef void (*Hexobj_constructor)(void*);
typedef void (*Hexobj_destructor)(void*);

typedef int Hex_type_s;

/*
 * Hex Object encapsulation
 */
typedef struct HexObject_s {
  void *obj;  	                  /* object data */
  Hex_size_t objlen;			  /* object size, in bytes */
  void *desc;                     /* object descriptor */
  Hexobj_constructor constructor; /* object constructor */
  Hexobj_destructor desctructor;  /* object destructor */
  Hex_type_s obj_type;			  /* object type */
} HexObject;


/*
 * Create a HexObject from a void pointer.
 */
HexObject* HexObj_FromVoidPtr(void* obj, Hex_size_t len, void *desc);


/*
 * Create a HexObject from a void pointer
 * by using the provided construtor, length and descriptor.
 * The object will be created by invoking the constructor. 
 */
HexObject* HexObj_FromVoidPtrAndCon(void* obj, Hex_size_t len, void* desc,
	Hexobj_constructor);


/*
 * Create a HexObject from a void pointer
 * by using the provided descriptor, constructor and destructor. 
 * The object will be destroyed with the provided destructor.
 */
HexObject* HexObj_FromVoidPtrAndConAndDes(void* obj, Hex_size_t len,
	void* desc, Hexobj_constructor, Hexobj_destructor);


/*
 * Get the underlying raw object of the HexObject. 
 */
void* HexObj_GetRawObj(HexObject*);


/*
 * Get the size(in bytes) of the underlying object. 
 */
Hex_size_t HexObj_GetSize(HexObject);


/*
 * Get the underlying descriptor of the HexObject.
 */
void* HexObj_GetDesc(HexObject*);


/*
 * Get the constructor of the HexObject.
 */
Hexobj_constructor HexObj_GetConstructor(HexObject*);


/*
 * Get the destructor of the HexObject.
 */
Hexobj_destructor HexObj_GetDestructor(HexObject*);


/*
 * Set the underlying raw object of HexObject.
 */
int HexObj_SetRawObj(HexObject*, void*);


/*
 * Set the size of the underlying object.
 */
int HexObj_SetSize(HexObject*, Hex_size_t);


/*
 * Set the underlying descriptor of HexObject.
 */
int HexObj_SetDesc(HexObject*, void*);


/*
 * Set the constructor of the HexObject. 
 */
int HexObj_SetConstructor(HexObject*, Hexobj_constructor);


/*
 * Set the destructor of the HexObject.
 */
int HexObj_SetDestructor(HexObject*, Hexobj_destructor);


#ifdef _cplusplus
}
#endif

#endif /* _HEX_OBJECT_H_ */
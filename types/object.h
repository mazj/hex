#ifndef HEX_OBJECT_H
#define HEX_OBJECT_H

#ifdef _cplusplus
extern "C" {
#endif


/*
 * Hex Object encapsulation
 */
typedef struct HexObject_s {
  void *obj;
  void *desc;
  void (*constructor)(void*);
  void (*destructor)(void*);
} HexObject;


/*
 * HexObject constructor and destructor. 
 */
typedef void (*hexobj_constructor)(void*);
typedef void (*hexobj_destructor)(void*);


/*
 * Create a HexObject from a void pointer.
 */
HexObject* HexObj_FromVoidPtr(void* obj, void *desc);


/*
 * Create a HexObject from a void pointer
 * by using the provided construtor and descriptor.
 * The object will be created by invoking the constructor. 
 */
HexObject* HexObj_FromVoidPtrAndCon(void* obj, void* desc,
	void (*construtor)(void*));


/*
 * Create a HexObject from a void pointer
 * by using the provided descriptor, constructor and destructor. 
 * The object will be destroyed with the provided destructor.
 */
HexObject* HexObj_FromVoidPtrAndConAndDes(void* obj, void* desc,
	void (*constructor)(void*), void (*destructor)(void*));


/*
 * Get the underlying raw object of the HexObject. 
 */
void* HexObj_GetRawObj(HexObject*);


/*
 * Get the underlying descriptor of the HexObject.
 */
void* HexObj_GetDesc(HexObject*);


/*
 * Get the constructor of the HexObject.
 */
hexobj_constructor HexObj_GetConstructor(HexObject*);


/*
 * Get the destructor of the HexObject.
 */
hexobj_destructor HexObj_GetDestructor(HexObject*);


/*
 * Set the underlying raw object of HexObject.
 */
int HexObj_SetRawObj(HexObject*, void*);


/*
 * Set the underlying descriptor of HexObject.
 */
int HexObj_SetDesc(HexObject*, void*);


/*
 * Set the constructor of the HexObject. 
 */
int HexObj_SetConstructor(HexObject*, void(*constructor)(void*));


/*
 * Set the destructor of the HexObject.
 */
int HexObj_SetDestructor(HexObject*, void(*destructor)(void*));


#ifdef _cplusplus
}
#endif

#endif // HEX_OBJECT_H
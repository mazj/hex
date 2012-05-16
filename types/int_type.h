/* HEX 32-bit integer. */

#ifndef _HEX_INT_OBJ_H_
#define _HEX_INT_OBJ_H_

#include "object.h"

#ifdef __cplusplus
extern "C" {
#endif


/*
 * Hex integer type(32bit).
 */
typedef struct HexIntObj_s {
	enum {
		hex_int_obj_type_int;
		hex_int_obj_type_uint;
	} hex_int_obj_type;
  	union {
  		int int_val;
  		unsigned uint_val;
	};
} HexIntObj;


/*
 * Max value of positive 32-bit unsigned integer (2^32-1)
 */
#define HEX_INT_MAX_UNSIGNED UINT_MAX

/*
 * Max value of positive 32-bit signed integer (2^31-1)
 */
#define HEX_INT_MAX_SIGNED   INT_MAX


/*
 * Min value of 32-bit signed integer  
 */
#define HEX_INT_MIN_SIGNED  INT_MIN


/*
 * Max value of 32 bit integer(2^32-1)
 */
#define HEX_INT_MAX HEX_INT_MAX_UNSIGNED   


/*
 * Convenience macro(use with caution).
 */
#define HexIntObj_AS_UINT(obj) (((HexIntObj*)(obj))->uint_val)
#define HexIntObj_AS_INT(obj)  (((HexIntObj*)(obj))->int_val)


int HexInt_GetMax();

/*
 * Get a HexObject from an unsigned integer.
 */
HexIntObj* HexIntObj_FromUnsignedInteger(unsigned int);


/*
 * Get a HexIntObj from a signed integer.
 */
HexIntObj* HexIntObj_FromSignedInteger(int);


/*
 * Get a HexObject from a long integer.
 */
HexIntObj* HexIntObj_FromLong(long);


/*
 * Get a HexObject from size_t.
 */
HexIntObj* HexIntObj_FromSize_t(size_t);


/*
 * Get a HexObject from a char.
 */
HexIntObj* HexIntObj_FromChar(char);


/*
 * Get a HexIntObj from a string.
 */
HexIntObj* HexIntObj_FromString(char*);


/*
 * Converts an integer to a given base in string format.
 * Accepting bases:
 *  - binary(base 2): prefix '0b' or '0B'
 *  - octal(base 8): prefix '0o' or '0O'
 *  - hexidecimal(base 16): prefix '0x' or '0X'
 */
HexObject* HexIntObj_FormatString(HexIntObj* obj, int base, int capital);




#ifdef __cplusplus
}
#endif

#endif /* _HEX_INT_OBJ_H_ */
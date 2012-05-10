/* 
 * HexIntObj represents a 32-bit immutable integer.
 */

#ifndef HEX_INT_OBJ_H
#define HEX_INT_OBJ_H

#include "hex.h"
#include "object.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Hex integer type(32bit).
 */
typedef struct HexIntObj_s {
  long int_val;
} HexIntObj;


/*
 * Max value of positive 32-bit unsigned integer (2^32-1)
 */
#define HEX_INT_MAX_UNSIGNED ULONG_MAX

/*
 * Max value of positive 32-bit signed integer (2^31-1)
 */
#define HEX_INT_MAX_SIGNED   LONG_MAX

/*
 * Min value of 32-bit signed integer  
 */
#define HEX_INT_MIN_SIGNED  LONG_MIN


/*
 * Max value of 32 bit integer(2^32-1)
 */
#define HEX_INT_MAX HEX_INT_MAX_UNSIGNED   


/*
 * Convenience macro(use with caution).
 */
#define HexInt_AS_LONG(obj) (((HexIntObj*)(obj))->int_val)

/*
 * Get a HexObject from a string.
 */
HexObject* HexIntObj_FromString(char*);


/*
 * Get a HexObject from a long integer.
 */
HexObject* HexIntObj_FromLong(long);


/*
 * Get a HexObject from size_t.
 */
HexObject* HexIntObj_FromSize_t(Hex_size_t);


/*
 * Get a HexObject from a char.
 */
HexObject* HexIntObj_FromChar(char);


/*
 * Converts an integer to a given base in string format.
 * Accepting bases:
 *  - binary(base 2): prefix '0b' or '0B'
 *  - octal(base 8): prefix '0o' or '0O'
 *  - hexidecimal(base 16): prefix '0x' or '0X'
 */
HexObject* HexIntObj_FormatString(HexIntObj* o, int base, int capital);




#ifdef __cplusplus
}
#endif

 #endif /* HEX_INT_OBJ_H */
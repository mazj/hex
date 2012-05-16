/* HEX 32-bit integer. */

#include "int_type.h"

int
HexInt_GetMax(void)
{
    return HEX_INT_MAX;
}

HexIntObj*
HexIntObj_FromUnsignedInteger(unsigned int uint_val)
{
    HexIntObj *obj = MALLOC(HexIntObj);

    obj->hex_int_obj_type = hex_int_obj_type_uint;
    obj->uint_val = uint_val;

    return obj;
}

HexIntObj*
HexIntObj_FromSignedInteger(int int_val)
{
    HexIntObj obj = MALLOC(HexIntObj);

    obj->hex_int_obj_type = hex_int_obj_type_int;
    obj->int_val = int_val;

    return obj;
}

HexIntObj*
HexIntObj_FromLong(long l)
{
    HexIntObj obj = MALLOC(HexIntObj);

    obj->hex_int_obj_type = hex_int_obj_type_int;
    obj->int_val = (int)int_val;

    return obj;
}

HexObject*
HexIntObj_FromSize_t(size_t t)
{
    if(t >= HEX_INT_MIN_SIGNED && t <= HEX_INT_MAX_SIGNED)
      return HexInt_FromUnsignedInteger((unsigned int)t);
}

HexIntObj*
HexIntObj_FromChar(char c)
{
    return HexIntObj_FromSignedInteger((int)c);
}

HexObject*
HexInt_FromString(char *str)
{
    int int_val = atoi(str);
    return int_val < 0 ? HexIntObj_FromSignedInteger(int_val)
      : HexIntObj_FromUnsignedInteger((unsigned int)int_val);
}

HexObject*
HexInt_FormatString(HexIntObject *obj, int base, int capital)
{
    assert(obj != NULL);

    int_val = obj->int_val;
    char *s = itoa_fmt(int_val, base, capital);
    return 0;
}
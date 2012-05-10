#include "int_type.h"

long
HexInt_GetMax(void) {
  return HEX_INT_MAX;
}

HexObject*
HexInt_FromLong(long l)
{
  register HexIntObj *obj;
  // HexObject_INIT(obj, &HexInt_Type);
  return (HexObject*)obj;	
}

HexObject*
HexInt_FromSize_t(Hex_size_t t)
{
  if(t >= HEX_INT_MIN_SIGNED && t <= HEX_INT_MAX_SIGNED)
  	return HexInt_FromLong((long)t);
}

Hex_size_t
HexInt_ConvertSize_t(HexObject* obj)
{
	if(!obj) {
		HEX_SET_ERR_STR(HEX_ERR_TYPE_ARG, "null arg");
        return -1;
    }

  	if(HexInt_Check(obj))
    	return HexInt_AS_LONG((HexIntObj*)obj);
  	if(HexLong_Check(obj))
		return HexLong_ConvertSize_t(obj);

    return HexInt_AsLong(obj);
}

HexObject*
HexInt_FromString(char *str, int base)
{
	if(!str) {
		HEX_SET_ERR_STR(HEX_ERR_TYPE_ARG, "null arg");
		return 0;
	}

    long val = itoa(str);

    return val;
}

HexObject*
HexInt_FormatString(HexIntObject *obj, int base, int capital)
{
	itoa_format(integer, base, capital);
}
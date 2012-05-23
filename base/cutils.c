#include <limits.h>
#include "strutils.h"
#include "assert.h"

char*
itoa(int value, char *str, int base)
{
	int isNegative = value < 0;

  	int v = value >= 0 ? : value * -1;
  	int v2 = v;
  	int numDigits = 0;
  	while(v >= 0) {
    	numDigits++;
    	if(v < 10) {
      		break;
    	} else {
      		v /= 10;
    	}
  	}

  	char *str_;
  	size_t len = (isNegative && base == 10) ?
  		numDigits + 2 : numDigits + 1;
  	str_ = (char*)malloc(len);

  	int i = numDigits - 1;
  	while(v2 >= 0) {
    	int c = v2 % 10;
    	str_[i] = c + '0';
    	v2 /= 10;
    	if(v2 == 0) {
      		break;
    	}
    	i--;
  	}

	if(base == 10 && isNegative) {
		str_[0] = '-';
  	}

  	str = str_;

  	return str;
}

int
atoi(const char *str)
{
	HEX_ASSERT(str != NULL);

	char *s = trim_hard(str);

	HEX_ASSERT(s != NULL);

	int val = 0;
	int isNegative = (*s == '-') ? 1 : 0;
	int i = (isdigit(*s)) ? 0 : 1;
	char *end = 0;

	char *ss = s;
	while(*ss != '\0') {
		if(isdigit(*ss)) {
			end = ss;
			ss++;	
		} else {
			break;
		}		
	}

	if(end == 0) {
		return 0;
	}

	int powerOfTen = 1;
	while(*end != s[i]) {
		val += (*end - '0') * powerOfTen;
		powerOfTen *= 10;
		end--;
	}

	val = isNegative ? val * -1 : val;

	HEX_ASSERT(val >= INT_MIN && val <= INT_MAX);

	return val;
}
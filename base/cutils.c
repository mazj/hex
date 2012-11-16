/*
 * HEX Programming Language
 * Copyright (C) 2012  Yanzheng Li
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "assert.h"
#include "memory.h"
#include "utils.h"


static
char* _itoa_base(int value, char *str, int base)
{
  unsigned int v = (unsigned int)value;

  const int buf_size=60;
  char buf[buf_size];
  int buf_index = 0;

  unsigned int remainder = 0;

  while(v >= base) {
    remainder = v % base;
    v /= base;
    buf[buf_index++] = remainder + '0';
  }

  if(v > 0) {
    buf[buf_index] = v + '0';
  }

  char *_str = (char*)MALLOC(buf_index+2);
  memset(_str, 0, buf_index+2);

  int str_index = 0;

  while(buf_index >= 0) {
    _str[str_index++] = buf[buf_index--];
  }

  *(&str) = _str;

  return str;
}


char*
itoa(int value, char *str, int base)
{
  if(base != 10 && value >= base)
    return _itoa_base(value, str, base);

  int isNegative = value < (int)0;

  int v = abs(value);
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

  size_t len = isNegative ?
    numDigits + 2 : numDigits + 1;

  char *_str = (char*)malloc(len);
  memset(_str, 0, len);

  HEX_ASSERT(_str);

  int i = len - 2;

  while(v2 >= 0) {
    int c = v2 % 10;
    _str[i] = c + '0';
    v2 /= 10;

    if(v2 == 0) {
      break;
    }

    i--;
  }

  if(isNegative) {
    _str[0] = '-';
  }

  *(&str) = _str;

  return str;
}

int
atoi(const char *str)
{
  RETURN_VAL_IF_NULL(str, 0);

  char *s = (char*)str;

  /* trim leading whitespaces */
  while(*s!='\0' && isspace(*s)) {
    s++;
  }

  RETURN_VAL_IF_NULL(s, 0);

  long val = 0;
  int isNegative = (*s == '-');
  char *end_ptr = 0;

  int start = (*s == '-' || *s == '+') ? 1 : 0;
  int end = -1 + start;

  /* potential start of the valid sequence of digits */
  char *ss = s+start;

  /* check the first digit in the sequence is a numeric digit. */
  RETURN_VAL_IF_FALSE(isdigit(*ss), 0);

  while(*ss!='\0') {
    if(isdigit(*ss)) {
      end_ptr = ss;
      ss++;
      end++;
    } else {
      break;
    }		
  }

  /* this is not a number */
  RETURN_VAL_IF_TRUE(end < start, 0);

  int powerOfTen = 1;
  while(end >= start) {
    char c = (char)*end_ptr;
    val += (long)( (long)(c - '0') * powerOfTen );
    powerOfTen *= 10;
    end_ptr--;
    end--;
  }

  val = isNegative ? val * (long)-1 : val;

  RETURN_VAL_IF_TRUE((int)val < INT_MIN, INT_MIN);
  RETURN_VAL_IF_TRUE((int)val > INT_MAX, INT_MAX);

  return (int)val;
}

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

#include <limits.h>
#include "strutils.h"
#include "assert.h"


char*
itoa(int value, char *str)
{
  RETURN_VAL_IF_NULL(str, NULL);

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

  size_t len = isNegative ?
    numDigits + 2 : numDigits + 1;

  char *_str = (char*)malloc(len);

  int i = numDigits - 1;

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

  str = _str;

  return str;
}

int
atoi(const char *str)
{
  HEX_ASSERT(str);

  char *s = strtrim(str);

  HEX_ASSERT(s);

  int val = 0;
  int isNegative = (*s == '-') ? 1 : 0;
  int start = (isdigit(*s)) ? 0 : 1;
  int end = -1;
  char *end_ptr = 0;

  char *ss = s;

  while(*ss != '\0') {
    if(isdigit(*ss)) {
      end_ptr = ss;
      ss++;
      end++;
    } else {
      break;
    }		
  }

  if(end < start) {  // this is not a number
    return 0;
  }

  int powerOfTen = 1;
  while(end >= start) {
    val += (*end_ptr - '0') * powerOfTen;
    powerOfTen *= 10;
    end_ptr--;
  }

  val = isNegative ? val * -1 : val;

  HEX_ASSERT(val >= INT_MIN && val <= INT_MAX);

  return val;
}
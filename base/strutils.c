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


#include "utils.h"
#include "memory.h"
#include "strutils.h"


char* strtoupper(char *s)
{
  RETURN_VAL_IF_NULL(s, NULL);

  char *str = s;

  while(*str != '\0') {
    *str = toupper(*str);
    str++;
  }

  return s;
}

char* strtolower(char *s)
{
  RETURN_VAL_IF_NULL(s, NULL);

  char *str = s;

  while(*str) {
    *str = tolower(*str);
    str++;
  }
  return s;
}

char* strcpy_hard(char *dst, const char *src)
{
  RETURN_VAL_IF_NULL(src, dst);

  size_t srclen = strlen(src);
  size_t dstlen = dst ? strlen(dst) : 0;
  size_t len = MAX(dstlen, srclen);

  if(dst) {
    free(dst);
  }

  dst = (char*)malloc(len+1);
  RETURN_VAL_IF_NULL(dst, NULL);

  strcpy(dst, src);

  return dst;
}

char* strtrim(char *s)
{
  RETURN_VAL_IF_NULL(s, NULL);

  size_t l = strlen(s);
  while(l > 1 && isspace(s[l-1])) s[--l] = '\0';
  while(*s && isspace(*s)) *s = '\0', ++s;
  return s;
}

size_t strlcpy2(char *dst, const char *src, size_t size)
{
  char *d = dst;
  const char *s = src;
  size_t n = size;

  if(n > 0) {
    while(--n != 0) {
      if((*d++ = *s++) == '\0') {
        break;
      }
    }
  }

  if(n == 0) {
    if(size != 0) {
      *d = '\0';
    }
    while(*s++) {} // do nothing
  }

  return s - src - 1;
}

char* strncpy_safe(char *dst, const char *src, size_t size)
{
  RETURN_VAL_IF_NULL(dst, NULL);
  RETURN_VAL_IF_NULL(src, NULL);

  size_t outlen = MIN(strlen(src), size);

  return strncpy(dst, src, outlen);
}

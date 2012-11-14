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

#include <stddef.h>
#include <string.h>
#include "hash.h"
#include "utils.h"

#define GOLDEN_PRIME 12347

/*************************************
 * Use Horner's rule to hash string.
 * O(n) runtime for short string.
 * ************************************/
static
unsigned long _hash_str_short(const char * str, size_t len)
{
  unsigned long h = 0;

  int i;
  for(i = 0; i < len; i++) {
    h = GOLDEN_PRIME * h + str[i];
  }

  return h;
}

/*************************************
 * Use Horner's rule to hash string.
 * O(ln(n)) runtime for long string.
 * ************************************/
static
unsigned long _hash_str_long(const char * str, size_t len)
{
  unsigned long h = 0;

  int i;
  for(i=1; i <= len; i*=2) {
    h = GOLDEN_PRIME * h + str[i-1];
  }

  return h;
}

unsigned long hash_str(const char * str)
{
  RETURN_VAL_IF_NULL(str, 0);

  size_t len = strlen(str);

  return len <= 20 ? _hash_str_short(str, len) : _hash_str_long(str, len);  
}

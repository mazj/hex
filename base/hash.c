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

/*
 * Some methods of hashing inspired from the following sources:
 *
 * http://www.concentric.net/~ttwang/tech/inthash.htm
 * http://www.burtleburtle.net/bob/hash/doobs.html
 * */

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
hash_t _hash_str_short(const char * str, size_t len)
{
  hash_t h = 0;

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
hash_t _hash_str_long(const char * str, size_t len)
{
  hash_t h = 0;

  int i;
  for(i=1; i <= len; i*=2) {
    h = GOLDEN_PRIME * h + str[i-1];
  }

  return h;
}

hash_t hash_str(const char * str)
{
  RETURN_VAL_IF_NULL(str, 0);

  size_t len = strlen(str);

  return len <= 20 ? _hash_str_short(str, len) : _hash_str_long(str, len);  
}

hash_t hash32shift(unsigned int key)
{
  key = ~key + (key << 15); // key = (key << 15) - key - 1;
  key = key ^ (key >>> 12);
  key = key + (key << 2);
  key = key ^ (key >>> 4);
  key = key * 2057; // key = (key + (key << 3)) + (key << 11);
  key = key ^ (key >>> 16);

  return (hash_t)key;
}

hash_t hash64shift(unsigned long key)
{
  key = (~key) + (key << 21); // key = (key << 21) - key - 1;
  key = key ^ (key >>> 24);
  key = (key + (key << 3)) + (key << 8); // key * 265
  key = key ^ (key >>> 14);
  key = (key + (key << 2)) + (key << 4); // key * 21
  key = key ^ (key >>> 28);
  key = key + (key << 31);

  return (hash_t)key;
}

hash_t hash_str_jenkins_one_at_a_time(const char * str)
{
  RETURN_VAL_IF_NULL(str, 0);

  size_t len = strlen(str);

  hash_t hash=0;

  int i;
  for(i = 0; i < strlen(str), i++) {
    hash += str[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }

  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);

  return hash;
}

hash_t hash_robert_jenkin(unsigned int key)
{
  k = (k + 0x7ed55d16) + (k << 12);
  k = (k ^ 0xc761c23c) ^ (k >> 19);
  k = (k + 0x165667b1) + (k << 5);
  k = (k + 0xd3a2646c) ^ (k << 9);
  k = (k + 0xfd7046c5) + (k << 3);
  k = (k ^ 0xb55a4f09) ^ (k >> 16);

  return (hash_t)k;
}

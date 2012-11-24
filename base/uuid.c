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
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include "uuid.h"
#include "rand.h"
#include "hash.h"


int uuid_create(hex_uuid_t *uuid)
{
  time_t t;
  char buf[30];
  unsigned long long ll;

  unsigned long  u1=0;
  unsigned long  u2=0;
  unsigned int   u3=0;
  unsigned short u4=0;
  unsigned short u5=0;

  t = time(NULL);
  snprintf(buf, sizeof(buf), "%lld", (unsigned long long)t);
  ll = (unsigned long long)t;

  u1 = (ll & 0xFFFF0000) >> 16;
  u2 = ll & 0xFFFF;
  u3 = hash_str(buf);
  u4 = (unsigned short)hex_rand_top(USHRT_MAX);
  u5 = (unsigned short)hex_rand_top(USHRT_MAX);

  uuid->time_u = u1;
  uuid->time_l = u2;
  uuid->time_h = u3;
  uuid->rand_1 = u4;
  uuid->rand_2 = u5;

  return 1;
}

int uuid_compare(hex_uuid_t uuid1, hex_uuid_t uuid2)
{
  RETURN_VAL_IF_NE(uuid1.time_u, uuid2.time_u, 0);
  RETURN_VAL_IF_NE(uuid1.time_l, uuid2.time_l, 0);
  RETURN_VAL_IF_NE(uuid1.time_h, uuid2.time_h, 0);
  RETURN_VAL_IF_NE(uuid1.rand_1, uuid2.rand_1, 0);
  RETURN_VAL_IF_NE(uuid1.rand_2, uuid2.rand_2, 0);

  return 1;
}

hash_t uuid_to_hash(const hex_uuid_t uuid)
{
  hash_t hash = 0;

  hash_t time_u_hash = (hash_t)hash64shift(uuid.time_u);
  hash_t time_l_hash = (hash_t)hash64shift(uuid.time_l);
  hash_t time_h_hash = (hash_t)hash64shift(uuid.time_h);
  hash_t rand_1_hash = (hash_t)hash_robert_jenkin((unsigned int)uuid.rand_1);
  hash_t rand_2_hash = (hash_t)hash_robert_jenkin((unsigned int)uuid.rand_2);

#ifndef GOLDEN_PRIME
#define GOLDEN_PRIME 37
#endif

  hash = hash * GOLDEN_PRIME + time_u_hash;
  hash = hash * GOLDEN_PRIME + time_l_hash;
  hash = hash * GOLDEN_PRIME + time_h_hash;
  hash = hash * GOLDEN_PRIME + rand_1_hash;
  hash = hash * GOLDEN_PRIME + rand_2_hash;

  return hash;
}

hash_t uuid_create_and_hash()
{
  hex_uuid_t uuid;

  int res = uuid_create(&uuid);

  return uuid_to_hash((const hex_uuid_t)uuid);
}

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


int uuid_create(hex_uuid_t* id)
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

  char *s = buf;
  unsigned int sum=0;
  while(*s) {
    sum += *s;
    s++;
  }

  u1 = (ll & 0xFFFF0000) >> 16;
  u2 = ll & 0xFFFF;
  u3 = sum;
  u4 = (unsigned short)hex_rand_top(USHRT_MAX);
  u5 = (unsigned short)hex_rand_top(USHRT_MAX);

  id->time_u = u1;
  id->time_l = u2;
  id->time_h = u3;
  id->rand_1 = u4;
  id->rand_2 = u5;

  return 1;
}

int uuid_compare(hex_uuid_t id1, hex_uuid_t id2)
{
  RETURN_VAL_IF_NE(id1.time_u, id2.time_u, 0);
  RETURN_VAL_IF_NE(id1.time_l, id2.time_l, 0);
  RETURN_VAL_IF_NE(id1.time_h, id2.time_h, 0);
  RETURN_VAL_IF_NE(id1.rand_1, id2.rand_1, 0);
  RETURN_VAL_IF_NE(id1.rand_2, id2.rand_2, 0);

  return 1;
}


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

#ifndef _UUID_H_
#define _UUID_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "rand.h"

typedef unsigned long long uuid_t;

static
const unsigned int GOLDEN_PRIME = 12347;

uuid_t uuid_from_str(char *str)
{
  RETURN_VAL_IF_NULL(str, (uuid_t)0);

  unsigned long long h = 0;

  int i;
  for(i = 1; i <= strlen(str); i*=2) {
    h = GOLDEN_PRIME * h + str[i-1];
  }

  return (uuid_t)h;
}

uuid uuid_create()
{
  time_t t;
  char buf[10];
  unsigned long u1;
  unsigned long u2;
  unsigned long u3;
  unsigned long u4;
  uuid_t id;
  unsigned char section_size = sizeof(uuid_t)/4;

  t = time(NULL);
  snprintf(buf, sizeof(buf), "%l", (unsigned long)t);

  u1 = (unsigned long)t;
  u2 = (unsigned long)uuid_from_str(buf);
  u3 = rand(ULONG_MAX);
  u4 = rand(ULONG_MAX);

  void *p = &u;

  memcpy(p, &u1, section_size); p+=section_size;
  memcpy(p, &u2, section_size); p+=section_size;
  memcpy(p, &u3, section_size); p+=section_size;
  memcpy(p, &u4, section_size);

  return (uuid_t)id;
}


#endif /* _UUID_H_ */

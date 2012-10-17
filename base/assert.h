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

/* General assertion */

#ifndef _ASSERT_H_
#define _ASSERT_H_


#include <stdio.h>
#include <stdlib.h>

#define HEX_ASSERT(expr)                                          \
  do {                                                            \
    if(expr == 0) {                                               \
      fprintf(stderr, "Assertion %s failed, "                     \
        "at %s[line %d]\n", #expr, __FILE__, __LINE__);           \
      abort();                                                    \
    }                                                             \
  } while(0)


#endif /* _ASSERT_H_ */
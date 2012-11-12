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

#include <string.h>
#include <limits.h>
#include "../unittest.h"
#include "../utils.h"
#include "../memory.h"
#include "../assert.h"


/**********************************
 * Test for:
 * MALLOC(size_)
 **********************************/
TEST(MALLOCTest, Malloc5BytesTest) {
  char *p = NULL;
  p = (char*)MALLOC(5);

  HEX_ASSERT(p);

  char s[] = "1234";
  strcpy(p, s);
  ASSERT_STREQ(s, p);
  ASSERT_EQ(strlen(s), strlen(p));
  free(p);
}


/**********************************
 * Test for:
 * HEX_MALLOC(T)
 **********************************/
TEST(HEX_MALLOCTest, HexMallocIntTest) {
  int *i = NULL;
  i = HEX_MALLOC(int);

  HEX_ASSERT(i);

  *i = 5;
  ASSERT_EQ(5, *i);
  free(i);
}

TEST(HEX_MALLOCTest, HexMallocOnStructTest) {
  struct SomeStruct {
    char c;
    short s;
    int i;
    long l;
  };

  struct SomeStruct *obj = NULL;
  obj = HEX_MALLOC(struct SomeStruct);

  HEX_ASSERT(obj);

  obj->c = SCHAR_MAX;
  obj->s = SHRT_MAX;
  obj->i = INT_MAX;
  obj->l = LONG_MAX;

  ASSERT_EQ(SCHAR_MAX, obj->c);
  ASSERT_EQ(SHRT_MAX, obj->s);
  ASSERT_EQ(INT_MAX, obj->i);
  ASSERT_EQ(LONG_MAX, obj->l);

  free(obj);
}

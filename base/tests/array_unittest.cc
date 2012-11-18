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
#include "../array.h"


class ArrayTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    _array = array_create();
    HEX_ASSERT(_array);
  }

  virtual void TearDown() {
    array_free(&_array);
    HEX_ASSERT(_array == NULL);
  }

  Array _array;
};

TEST_F(ArrayTest, ArrayCreationTest) {
  HEX_ASSERT(_array);
  ASSERT_EQ(0, array_size(_array));
}

TEST_F(ArrayTest, ArrayAppendTest1) {
  int numbers[] = {1,2,3,4,5,6,7,8,9,10};
  int i;

  for(i = 0; i < 10; i++) {
    array_append(_array, &numbers[i]);
    ASSERT_EQ(i+1, array_size(_array));
  }

  for(i = 0; i < 10; i++) {
    void *p = array_get(_array, i);
    int val = DEREF_VOID(int, p);
    ASSERT_EQ(numbers[i], val);
    ASSERT_EQ(10, array_size(_array));
  }

  ASSERT_EQ(10, array_size(_array));
}

TEST_F(ArrayTest, ArrayAppendTest2) {
  int numbers[] = {1,2,3,4,5,6,7,8,9,10};
  int i;

  for(i = 0; i < 10; i++) {
    array_append(_array, &numbers[i]);
    ASSERT_EQ(i+1, array_size(_array));
  }

  for(i = 0; i < 10; i++) {
    void *p = array_remove(_array, 0);
    int val = DEREF_VOID(int, p);
    ASSERT_EQ(numbers[i], val);
    ASSERT_EQ(10-i-1, array_size(_array));
  }

  ASSERT_EQ(0, array_size(_array));
}

TEST_F(ArrayTest, ArrayRemoveTest1) {
  int odds[] = {1,3,5,7,9};
  int evens[] = {2,4,6,8,10};
  int i;

  for(i = 0; i < 5; i++) {
    array_append(_array, &odds[i]);
    ASSERT_EQ(i+1, array_size(_array));
  }

  /* array = {1,3,5,7,9} */
  {
    int val = DEREF_VOID(int, array_remove(_array, 1));
    ASSERT_EQ(3, val);
    ASSERT_EQ(4, array_size(_array));
  }

  /* array = {1,5,7,9} */
  {
    int val = DEREF_VOID(int, array_remove(_array, 2));
    ASSERT_EQ(7, val);
    ASSERT_EQ(3, array_size(_array));
  }

  /* array = {1,5,9} */
  {
    int val = DEREF_VOID(int, array_remove(_array, 2));
    ASSERT_EQ(9, val);
    ASSERT_EQ(2, array_size(_array));
  }

  /* array = {1,5} */
  {
    int val = DEREF_VOID(int, array_remove(_array, 0));
    ASSERT_EQ(1, val);
    ASSERT_EQ(1, array_size(_array));
  }

  /* array = {5} */
  {
    int val = DEREF_VOID(int, array_remove(_array, 0));
    ASSERT_EQ(5, val);
    ASSERT_EQ(0, array_size(_array));
  }
}

TEST_F(ArrayTest, ArrayRemoveAndSetTest) {
  int odds[] = {1,3,5,7,9};
  int evens[] = {2,4,6,8,10};
  int i;

  for(i = 0; i < 5; i++) {
    array_append(_array, &odds[i]);
    ASSERT_EQ(i+1, array_size(_array));
  }

  for(i = 0; i < 5; i++) {
    int val = DEREF_VOID(int, array_set(_array, i, &evens[i]));
    ASSERT_EQ(odds[i], val);
    val = DEREF_VOID(int, array_get(_array, i));
    ASSERT_EQ(evens[i], val);
    ASSERT_EQ(5, array_size(_array));
  }

  ASSERT_EQ(5, array_size(_array));

  for(i = 4; i >= 0; i--) {
    int val = DEREF_VOID(int, array_remove(_array, i));
    ASSERT_EQ(evens[i], val);
    ASSERT_EQ(i, array_size(_array));
  }

  ASSERT_EQ(0, array_size(_array));
}

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
#include "../bst.h"


class BstTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    _bst = bst_create();
    HEX_ASSERT(_bst);
  }

  virtual void TearDown() {
    bst_free(&_bst);
    HEX_ASSERT(_bst == NULL);
  }

  Bst _bst;
};

static
int bst_int_cmp(void *arg1, void *arg2)
{
  int val1 = DEREF_VOID(int, arg1);
  int val2 = DEREF_VOID(int, arg2);

  return val1 == val2 ? 0 : val1 < val2 ? -1 : 1;
}

TEST_F(BstTest, BstCreationTest) {
  HEX_ASSERT(_bst);
  ASSERT_EQ(0, bst_size(_bst));
  ASSERT_EQ(0, bst_height(_bst));
}

TEST_F(BstTest, BstInsertAndFindTest) {
  int numbers[] = {5,8,2,1,10,7,3,6,4,9};
  int i;

  for(i = 0; i < 10; i++) {
    ASSERT_EQ(1, bst_insert(_bst, &numbers[i], sizeof(int), bst_int_cmp));
    ASSERT_EQ(i+1, bst_size(_bst));
    ASSERT_LE(0, bst_height(_bst));
  }

  for(i = 0; i < 10; i++) {
    void *p = bst_find(_bst, &numbers[i], bst_int_cmp); 
    int val = DEREF_VOID(int, p);
    ASSERT_EQ(numbers[i], val);
    ASSERT_EQ(10, bst_size(_bst));
  }

  ASSERT_EQ(10, bst_size(_bst));
  ASSERT_LE(0, bst_height(_bst));
}

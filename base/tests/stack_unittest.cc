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
#include "../stack.h"


class StackTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    _stack = stack_create();
    HEX_ASSERT(_stack);
  }

  virtual void TearDown() {
    stack_free(&_stack);
    HEX_ASSERT(_stack == NULL);
  }

  Stack _stack;
};


TEST_F(StackTest, StackCreationTest) {
  HEX_ASSERT(_stack);
  ASSERT_EQ(0, stack_size(_stack));
  HEX_ASSERT(stack_pop(_stack) == NULL);
}

TEST_F(StackTest, StackPushPopTest1) {
  int numbers[] = {1,2,3,4,5,6,7,8,9,10};
  int i;
  for(i = 0; i < 10; i++) {
    stack_push(_stack, &numbers[i], sizeof(int));
  }

  ASSERT_EQ(10, stack_size(_stack));

  for(i = 9; i >= 0; i--) {
    int *p = (int*)stack_pop(_stack);
    int val = DEREF_VOID(int, p);
    ASSERT_EQ(numbers[i], val);
  }

  HEX_ASSERT(stack_pop(_stack) == NULL);

  ASSERT_EQ(0, stack_size(_stack));
}

TEST_F(StackTest, StackPushPopTest2) {
  int odds[] = {1,3,5,7,9};
  int evens[] = {2,4,6,8,10};
  
  int i;
  for(i = 0; i < 5; i++) {
    stack_push(_stack, &odds[i], sizeof(int));
  }

  ASSERT_EQ(5, stack_size(_stack));

  for(i = 4; i >= 0; i--) {
    int *p = (int*)stack_pop(_stack);
    int val = DEREF_VOID(int, p);
    ASSERT_EQ(odds[i], val);
  }

  HEX_ASSERT(stack_pop(_stack) == NULL);
  ASSERT_EQ(0, stack_size(_stack));

  for(i = 0; i < 5; i++) {
    stack_push(_stack, &evens[i], sizeof(int));
  }

  ASSERT_EQ(5, stack_size(_stack));

  for(i = 4; i >= 0; i--) {
    int *p = (int*)stack_pop(_stack);
    int val = DEREF_VOID(int, p);
    ASSERT_EQ(evens[i], val);
  }

  HEX_ASSERT(stack_pop(_stack) == NULL);
  ASSERT_EQ(0, stack_size(_stack));
}

TEST_F(StackTest, StackPushPopTest3) {
  const char *fruits[26] = {
    "Apple", "Banana", "Coconut", "Dragonfruit", "Elephant apple",
    "Finger lime", "Grape", "Honeydrew melon", "Indian prune",
    "Jasmine", "Kiwi", "Lemon", "Melon", "Nannyberry", "Orange", "Peach",
    "Quandong", "Raspberry", "Strawberry", "Tangerine", "Uva",
    "Vanilla", "Watermelon", "Xylocarp", "Yamamomo", "Zucchini"
  };

  int i;
  for(i = 0; i < 26; i++) {
    char *fruit = (char*)fruits[i];
    stack_push(_stack, fruit, strlen(fruit)+1);
    ASSERT_EQ(i+1, stack_size(_stack));
  }

  ASSERT_EQ(26, stack_size(_stack));

  for(i = 25; i >= 0; i--) {
    char *fruit = (char*)stack_pop(_stack);
    ASSERT_STREQ(fruit, fruits[i]);
    ASSERT_EQ(i, stack_size(_stack));
  }

  ASSERT_EQ(0, stack_size(_stack));
  HEX_ASSERT(stack_pop(_stack) == NULL);
}

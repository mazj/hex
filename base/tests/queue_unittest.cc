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
#include "../queue.h"


class QueueTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    _queue = queue_create();
    HEX_ASSERT(_queue);
  }

  virtual void TearDown() {
    queue_free(&_queue);
    HEX_ASSERT(_queue == NULL);
  }

  Queue _queue;
};


TEST_F(QueueTest, QueueCreationTest) {
  HEX_ASSERT(_queue);
  ASSERT_EQ(0, queue_size(_queue));
  HEX_ASSERT(queue_pop(_queue) == NULL);
}

TEST_F(QueueTest, QueuePushPopTest1) {
  int numbers[] = {1,2,3,4,5,6,7,8,9,10};
  int i;
  for(i = 0; i < 10; i++) {
    queue_push(_queue, &numbers[i], sizeof(int));
  }

  ASSERT_EQ(10, queue_size(_queue));

  for(i = 0; i < 10; i++) {
    int *p = (int*)queue_pop(_queue);
    int val = DEREF_VOID(int, p);
    ASSERT_EQ(numbers[i], val);
  }

  HEX_ASSERT(queue_pop(_queue) == NULL);

  ASSERT_EQ(0, queue_size(_queue));
}

TEST_F(QueueTest, QueuePushPopTest2) {
  int odds[] = {1,3,5,7,9};
  int evens[] = {2,4,6,8,10};
  
  int i;
  for(i = 0; i < 5; i++) {
    queue_push(_queue, &odds[i], sizeof(int));
  }

  ASSERT_EQ(5, queue_size(_queue));

  for(i = 0; i < 5; i++) {
    int *p = (int*)queue_pop(_queue);
    int val = DEREF_VOID(int, p);
    ASSERT_EQ(odds[i], val);
  }

  HEX_ASSERT(queue_pop(_queue) == NULL);
  ASSERT_EQ(0, queue_size(_queue));

  for(i = 0; i < 5; i++) {
    queue_push(_queue, &evens[i], sizeof(int));
  }

  ASSERT_EQ(5, queue_size(_queue));

  for(i = 0; i < 5; i++) {
    int *p = (int*)queue_pop(_queue);
    int val = DEREF_VOID(int, p);
    ASSERT_EQ(evens[i], val);
  }

  HEX_ASSERT(queue_pop(_queue) == NULL);
  ASSERT_EQ(0, queue_size(_queue));
}

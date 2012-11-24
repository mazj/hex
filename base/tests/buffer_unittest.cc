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
#include "../buffer.h"

#define BUFFER_SIZE 1024

class BufferTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    _buffer = buffer_create(BUFFER_SIZE);
    HEX_ASSERT(_buffer);
  }

  virtual void TearDown() {
    buffer_free(&_buffer);
    HEX_ASSERT(_buffer == NULL);
  }

  Buffer _buffer;
};


TEST_F(BufferTest, BufferCreationTest) {
  HEX_ASSERT(_buffer);
}

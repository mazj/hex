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
#include "../memory.h"
#include "../assert.h"
#include "../strbuf.h"


class StrbufTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    _strbuf = strbuf_create();
    HEX_ASSERT(_strbuf);
  }

  virtual void TearDown() {
    strbuf_free(&_strbuf);
    HEX_ASSERT(_strbuf == NULL);
  }

  Strbuf _strbuf;
};


TEST_F(StrbufTest, StrbufCreationTest) {
  HEX_ASSERT(_strbuf);
  HEX_ASSERT(strbuf_cstr(_strbuf));
}

TEST_F(StrbufTest, StrbufAppendTest1) {
  char text[] = "Testing strbuf";
  strbuf_append(_strbuf, text);
  ASSERT_STREQ(text, strbuf_cstr(_strbuf));
  ASSERT_EQ(strlen(text), strbuf_len(_strbuf));
  ASSERT_LE(0, strbuf_capacity(_strbuf));
}

TEST_F(StrbufTest, StrbufAppendTest2) {
  char text1[] = "5 km a day, ";
  char text2[] = "keep the doctor away!";

  strbuf_append(_strbuf, text1);
  strbuf_append(_strbuf, text2);

  ASSERT_EQ(strlen(text1) + strlen(text2), strbuf_len(_strbuf));
  ASSERT_STREQ("5 km a day, keep the doctor away!", strbuf_cstr(_strbuf));
  ASSERT_LE(0, strbuf_capacity(_strbuf));
}

TEST_F(StrbufTest, StrbufAppendTest3) {
  char text1[] = "Apple, banana, coconut";
  char text2[] = "Airplane, boat, car";

  ASSERT_STREQ("", strbuf_cstr(_strbuf));

  strbuf_append(_strbuf, text1);

  ASSERT_EQ(strlen(text1), strbuf_len(_strbuf));
  ASSERT_STREQ(text1, strbuf_cstr(_strbuf));
  ASSERT_LE(0, strbuf_capacity(_strbuf));

  strbuf_empty(_strbuf);

  ASSERT_STREQ("", strbuf_cstr(_strbuf));
  ASSERT_EQ(0, strbuf_len(_strbuf));
  ASSERT_LE(0, strbuf_capacity(_strbuf));

  strbuf_append(_strbuf, text2);

  ASSERT_EQ(strlen(text2), strbuf_len(_strbuf));
  ASSERT_STREQ(text2, strbuf_cstr(_strbuf));
  ASSERT_LE(0, strbuf_capacity(_strbuf));
}

TEST_F(StrbufTest, StrbufEmptyTest) {
  char text[] = "Another test for strbuf";
  strbuf_append(_strbuf, text);
  ASSERT_STREQ(text, strbuf_cstr(_strbuf));
  ASSERT_EQ(strlen(text), strbuf_len(_strbuf));

  /* Empty strbuf */
  strbuf_empty(_strbuf);

  ASSERT_EQ(0, strbuf_len(_strbuf));
  ASSERT_LE(0, strbuf_capacity(_strbuf));
}


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

#include "../unittest.h"
#include "../assert.h"
#include "../hash.h"


/********************************************
 * Test for:
 * unsigned long hash_str(const char * str)
 ********************************************/
TEST(hash_strTest, HashNullStringTest) {
  ASSERT_EQ(hash_str(NULL), hash_str(NULL));
}

TEST(hash_strTest, HashOneCharacterStringTest1) {
  ASSERT_EQ(hash_str("c"), hash_str("c"));
}

TEST(hash_strTest, HashOneCharacterStringTest2) {
  ASSERT_NE(hash_str("a"), hash_str(NULL));
}

TEST(hash_strTest, HashOneCharacterStringTest3) {
  ASSERT_NE(hash_str("0"), hash_str("z"));
}

TEST(hash_strTest, HashShortStringTest1) {
  ASSERT_EQ(hash_str("hash string"), hash_str("hash string"));
}

TEST(hash_strTest, HashShortStringTest2) {
  ASSERT_NE(hash_str("hash another string"), hash_str(NULL)); 
}

TEST(hash_strTest, HashShortStringTest3) {
  ASSERT_EQ(hash_str("abbcccbba"), hash_str("abbcccbba"));
}

TEST(hash_strTest, HashShortStringTest4) {
  ASSERT_EQ(hash_str("   "), hash_str("   "));
}

TEST(hash_strTest, HashShortStringTest5) {
  ASSERT_NE(hash_str(" "), hash_str("     "));
}

TEST(hash_strTest, HashShortStringTest6) {
  ASSERT_EQ(hash_str(""), hash_str(NULL));
}

TEST(hash_strTest, HashLongStringTest1) {
  char str[] = "hash a string to test hash a string then hash another string";
  ASSERT_EQ(
    hash_str(str),
    hash_str(str)
  );
}

TEST(hash_strTest, HashLongStringTest2) {
  ASSERT_NE(
    hash_str("put .gitignore in .gitignore to make git ignore .gitignore"),
    hash_str(NULL)
  ); 
}

TEST(hash_strTest, HashLongStringTest3) {
  char palindrome[] = "abbcccddddeeeeeffffffgggggggffffffeeeeeddddcccbba";
  ASSERT_EQ(
    hash_str(palindrome),
    hash_str(palindrome)
  );
}

TEST(hash_strTest, HashLongStringTest4) {
  ASSERT_EQ(
    hash_str("                                                               "),
    hash_str("                                                               ")
  );
}

TEST(hash_strTest, HashLongStringTest5) {
  ASSERT_NE(
    hash_str(" "),
    hash_str("                                                               ")
  );
}

TEST(hash_strTest, HashLongStringTest6) {
  ASSERT_NE(
    hash_str("                                                               "),
    hash_str(NULL)
  );
}

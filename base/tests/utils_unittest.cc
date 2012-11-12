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
#include "../utils.h"


/*******************************************
 * Tests for MAX(a,b)
 *******************************************/
TEST(MaxTest, MaxOfPositiveInteger) {
  EXPECT_EQ(6, MAX(5,6));
  EXPECT_EQ(6, MAX(0,6));
}

TEST(MaxTest, MaxOfNegativeInteger) {
  EXPECT_EQ(-5, MAX(-5,-6));
  EXPECT_EQ(0, MAX(-5,0));
}

TEST(MaxTest, MaxOfPositiveFloatingNumber) {
  EXPECT_EQ(880.0f, MAX(0.2f, 880.0f));
  EXPECT_EQ(0.1f, MAX(0.0f, 0.1f));
}

TEST(MaxTest, MaxOfNegativeFloatingNumber) {
  EXPECT_EQ(-5.0f, MAX(-5.0f, -6.0f));
  EXPECT_EQ(0.0f, MAX(-5.0f, 0.0f));
}


/*******************************************
 * Tests for MIN(a,b)
 *******************************************/
TEST(MinTest, MinOfPositiveInteger) {
  EXPECT_EQ(5, MIN(5,6));
  EXPECT_EQ(0, MIN(5,0));
}

TEST(MinTest, MinOfNegativeInteger) {
  EXPECT_EQ(-6, MIN(-5, -6));
  EXPECT_EQ(-6, MIN(0, -6));
}

TEST(MinTest, MinOfPositiveFloatingNumber) {
  EXPECT_EQ(5.0f, MIN(5.0f, 6.0f));
  EXPECT_EQ(0.0f, MIN(0.0f, 5.0f));
}

TEST(MinTest, MinOfNegativeFloatingNumber) {
  EXPECT_EQ(-6.0f, MIN(-5.0f, -6.0f));
  EXPECT_EQ(-6.0f, MIN(0.0f, -6.0f));
}


/*******************************************
 * Tests for:
 * void set_nth_bit(int *val, char bit) 
 *******************************************/
TEST(SetNthBitTest, Set1stBit) {
  int val=0;
  set_nth_bit(&val, 1);
  EXPECT_EQ(0x00000001, val);
}

TEST(SetNthBitTest, Set2ndBit) {
  int val=0;
  set_nth_bit(&val, 2);
  EXPECT_EQ(0x00000002, val);
}

TEST(SetNthBitTest, Set4thBit) {
  int val=0;
  set_nth_bit(&val, 4);
  EXPECT_EQ(0x000000008, val);
}

TEST(SetNthBitTest, Set8thBit) {
  int val=0;
  set_nth_bit(&val, 8);
  EXPECT_EQ(128, val);
}

TEST(SetNthBitTest, Set16thBit) {
  int val=0;
  set_nth_bit(&val, 16);
  EXPECT_EQ(32768, val);
}

TEST(SetNthBitTest, Set32thBit) {
  int val=0;
  set_nth_bit(&val, 32);
  unsigned int val2 = 1;
  val2 <<= 31;

  EXPECT_EQ((int)((val2)*(-1)), val);
}

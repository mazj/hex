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
#include "../cutils.h"


/**********************************************
 * Test for:
 * char* itoa(int value, char *str, int base);
 **********************************************/
TEST(itoaTest, Base10_OneDigitZeroIntegerTest) {
  char *str=NULL;
  str = itoa(0, str, 10);
  ASSERT_STREQ("0", str); 
  HEX_FREE(str);
}

TEST(itoaTest, Base10_OneDigitPositiveIntegerTest1) {
  char *str=NULL;
  str = itoa(1, str, 10);
  ASSERT_STREQ("1", str); 
  HEX_FREE(str);
}

TEST(itoaTest, Base10_OneDigitPositiveIntegerTest2) {
  char *str=NULL;
  str = itoa(9, str, 10);
  ASSERT_STREQ("9", str); 
  HEX_FREE(str);
}

TEST(itoaTest, Base10_TwoDigitPositiveIntegerTest1) {
  char *str=NULL;
  str = itoa(12, str, 10);
  ASSERT_STREQ("12", str); 
  HEX_FREE(str);
}

TEST(itoaTest, Base10_TwoDigitPositiveIntegerTest2) {
  char *str=NULL;
  str = itoa(10, str, 10);
  ASSERT_STREQ("10", str); 
  HEX_FREE(str);
}

TEST(itoaTest, Base10_ThreeDigitPositiveIntegerTest1) {
  char *str=NULL;
  str = itoa(123, str, 10);
  ASSERT_STREQ("123", str); 
  HEX_FREE(str);
}

TEST(itoaTest, Base10_ThreeDigitPositiveIntegerTest2) {
  char *str=NULL;
  str = itoa(120, str, 10);
  ASSERT_STREQ("120", str); 
  HEX_FREE(str);
}

TEST(itoaTest, Base10_ThreeDigitPositiveIntegerTest3) {
  char *str=NULL;
  str = itoa(103, str, 10);
  ASSERT_STREQ("103", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_FourDigitPositiveIntegerTest1) {
  char *str=NULL;
  str = itoa(1234, str, 10);
  ASSERT_STREQ("1234", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_FourDigitPositiveIntegerTest2) {
  char *str=NULL;
  str = itoa(1230, str, 10);
  ASSERT_STREQ("1230", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_FourDigitPositiveIntegerTest3) {
  char *str=NULL;
  str = itoa(1204, str, 10);
  ASSERT_STREQ("1204", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_FourDigitPositiveIntegerTest4) {
  char *str=NULL;
  str = itoa(1034, str, 10);
  ASSERT_STREQ("1034", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_FiveDigitPositiveIntegerTest1) {
  char *str=NULL;
  str = itoa(12345, str, 10);
  ASSERT_STREQ("12345", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_FiveDigitPositiveIntegerTest2) {
  char *str=NULL;
  str = itoa(12340, str, 10);
  ASSERT_STREQ("12340", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_FiveDigitPositiveIntegerTest3) {
  char *str=NULL;
  str = itoa(12305, str, 10);
  ASSERT_STREQ("12305", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_FiveDigitPositiveIntegerTest4) {
  char *str=NULL;
  str = itoa(12045, str, 10);
  ASSERT_STREQ("12045", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_FiveDigitPositiveIntegerTest5) {
  char *str=NULL;
  str = itoa(10345, str, 10);
  ASSERT_STREQ("10345", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_SixDigitPositiveIntegerTest1) {
  char *str=NULL;
  str = itoa(123456, str, 10);
  ASSERT_STREQ("123456", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_SixDigitPositiveIntegerTest2) {
  char *str=NULL;
  str = itoa(123450, str, 10);
  ASSERT_STREQ("123450", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_SixDigitPositiveIntegerTest3) {
  char *str=NULL;
  str = itoa(123406, str, 10);
  ASSERT_STREQ("123406", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_SixDigitPositiveIntegerTest4) {
  char *str=NULL;
  str = itoa(123056, str, 10);
  ASSERT_STREQ("123056", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_SixDigitPositiveIntegerTest5) {
  char *str=NULL;
  str = itoa(120456, str, 10);
  ASSERT_STREQ("120456", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_SixDigitPositiveIntegerTest6) {
  char *str=NULL;
  str = itoa(103456, str, 10);
  ASSERT_STREQ("103456", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_SevenDigitPositiveIntegerTest1) {
  char *str=NULL;
  str = itoa(1234567, str, 10);
  ASSERT_STREQ("1234567", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_SevenDigitPositiveIntegerTest2) {
  char *str=NULL;
  str = itoa(1234560, str, 10);
  ASSERT_STREQ("1234560", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_SevenDigitPositiveIntegerTest3) {
  char *str=NULL;
  str = itoa(1234507, str, 10);
  ASSERT_STREQ("1234507", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_SevenDigitPositiveIntegerTest4) {
  char *str=NULL;
  str = itoa(1234067, str, 10);
  ASSERT_STREQ("1234067", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_SevenDigitPositiveIntegerTest5) {
  char *str=NULL;
  str = itoa(1230567, str, 10);
  ASSERT_STREQ("1230567", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_SevenDigitPositiveIntegerTest6) {
  char *str=NULL;
  str = itoa(1204567, str, 10);
  ASSERT_STREQ("1204567", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_SevenDigitPositiveIntegerTest7) {
  char *str=NULL;
  str = itoa(1034567, str, 10);
  ASSERT_STREQ("1034567", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_EightDigitPositiveIntegerTest1) {
  char *str=NULL;
  str = itoa((int)12345678, str, 10);
  ASSERT_STREQ("12345678", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_EightDigitPositiveIntegerTest2) {
  char *str=NULL;
  str = itoa((int)12345670, str, 10);
  ASSERT_STREQ("12345670", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_EightDigitPositiveIntegerTest3) {
  char *str=NULL;
  str = itoa((int)12345608, str, 10);
  ASSERT_STREQ("12345608", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_EightDigitPositiveIntegerTest4) {
  char *str=NULL;
  str = itoa((int)12345078, str, 10);
  ASSERT_STREQ("12345078", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_EightDigitPositiveIntegerTest5) {
  char *str=NULL;
  str = itoa((int)12340678, str, 10);
  ASSERT_STREQ("12340678", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_EightDigitPositiveIntegerTest6) {
  char *str=NULL;
  str = itoa((int)12305678, str, 10);
  ASSERT_STREQ("12305678", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_EightDigitPositiveIntegerTest7) {
  char *str=NULL;
  str = itoa((int)12045678, str, 10);
  ASSERT_STREQ("12045678", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_EightDigitPositiveIntegerTest8) {
  char *str=NULL;
  str = itoa((int)10345678, str, 10);
  ASSERT_STREQ("10345678", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_NineDigitPositiveIntegerTest1) {
  char *str=NULL;
  str = itoa((int)123456789, str, 10);
  ASSERT_STREQ("123456789", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_NineDigitPositiveIntegerTest2) {
  char *str=NULL;
  str = itoa((int)123456780, str, 10);
  ASSERT_STREQ("123456780", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_NineDigitPositiveIntegerTest3) {
  char *str=NULL;
  str = itoa((int)123456709, str, 10);
  ASSERT_STREQ("123456709", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_NineDigitPositiveIntegerTest4) {
  char *str=NULL;
  str = itoa((int)123456089, str, 10);
  ASSERT_STREQ("123456089", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_NineDigitPositiveIntegerTest5) {
  char *str=NULL;
  str = itoa((int)123450789, str, 10);
  ASSERT_STREQ("123450789", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_NineDigitPositiveIntegerTest6) {
  char *str=NULL;
  str = itoa((int)123406789, str, 10);
  ASSERT_STREQ("123406789", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_NineDigitPositiveIntegerTest7) {
  char *str=NULL;
  str = itoa((int)123056789, str, 10);
  ASSERT_STREQ("123056789", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_NineDigitPositiveIntegerTest8) {
  char *str=NULL;
  str = itoa((int)120456789, str, 10);
  ASSERT_STREQ("120456789", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_NineDigitPositiveIntegerTest9) {
  char *str=NULL;
  str = itoa((int)103456789, str, 10);
  ASSERT_STREQ("103456789", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_TenDigitPositiveIntegerTest1) {
  char *str=NULL;
  str = itoa((int)1234567891, str, 10);
  ASSERT_STREQ("1234567891", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_TenDigitPositiveIntegerTest2) {
  char *str=NULL;
  str = itoa((int)1234567890, str, 10);
  ASSERT_STREQ("1234567890", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_TenDigitPositiveIntegerTest3) {
  char *str=NULL;
  str = itoa((int)1234567801, str, 10);
  ASSERT_STREQ("1234567801", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_TenDigitPositiveIntegerTest4) {
  char *str=NULL;
  str = itoa((int)1234567091, str, 10);
  ASSERT_STREQ("1234567091", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_TenDigitPositiveIntegerTest5) {
  char *str=NULL;
  str = itoa((int)1234560891, str, 10);
  ASSERT_STREQ("1234560891", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_TenDigitPositiveIntegerTest6) {
  char *str=NULL;
  str = itoa((int)1234507891, str, 10);
  ASSERT_STREQ("1234507891", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_TenDigitPositiveIntegerTest7) {
  char *str=NULL;
  str = itoa((int)1234067891, str, 10);
  ASSERT_STREQ("1234067891", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_TenDigitPositiveIntegerTest8) {
  char *str=NULL;
  str = itoa((int)1230567891, str, 10);
  ASSERT_STREQ("1230567891", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_TenDigitPositiveIntegerTest9) {
  char *str=NULL;
  str = itoa((int)1204567891, str, 10);
  ASSERT_STREQ("1204567891", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_TenDigitPositiveIntegerTest10) {
  char *str=NULL;
  str = itoa((int)1034567891, str, 10);
  ASSERT_STREQ("1034567891", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_MaxPositiveIntegerTest) {
  /* This test MAY fail.
   * INT_MAX may be different on different platforms.
   * */
  char *str=NULL;
  str = itoa(INT_MAX, str, 10);
  ASSERT_STREQ("2147483647", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_OneDigitNegativeIntegerTest1) {
  char *str=NULL;
  str = itoa((int)-1, str, 10);
  ASSERT_STREQ("-1", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_OneDigitNegativeIntegerTest2) {
  char *str=NULL;
  str = itoa((int)-9, str, 10);
  ASSERT_STREQ("-9", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_TwoDigitNegativeIntegerTest1) {
  char *str=NULL;
  str = itoa(-12, str, 10);
  ASSERT_STREQ("-12", str); 
  HEX_FREE(str);
}

TEST(itoaTest, Base10_TwoDigitNegativeIntegerTest2) {
  char *str=NULL;
  str = itoa(-10, str, 10);
  ASSERT_STREQ("-10", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_ThreeDigitNegativeIntegerTest1) {
  char *str=NULL;
  str = itoa(-123, str, 10);
  ASSERT_STREQ("-123", str); 
  HEX_FREE(str);
}

TEST(itoaTest, Base10_ThreeDigitNegativeIntegerTest2) {
  char *str=NULL;
  str = itoa(-120, str, 10);
  ASSERT_STREQ("-120", str); 
  HEX_FREE(str);
}

TEST(itoaTest, Base10_ThreeDigitNegativeIntegerTest3) {
  char *str=NULL;
  str = itoa(-103, str, 10);
  ASSERT_STREQ("-103", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_FourDigitNegativeIntegerTest1) {
  char *str=NULL;
  str = itoa(-1234, str, 10);
  ASSERT_STREQ("-1234", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_FourDigitNegativeIntegerTest2) {
  char *str=NULL;
  str = itoa(-1230, str, 10);
  ASSERT_STREQ("-1230", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_FourDigitNegativeIntegerTest3) {
  char *str=NULL;
  str = itoa(-1204, str, 10);
  ASSERT_STREQ("-1204", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_FourDigitNegativeIntegerTest4) {
  char *str=NULL;
  str = itoa(-1034, str, 10);
  ASSERT_STREQ("-1034", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_FiveDigitNegativeIntegerTest1) {
  char *str=NULL;
  str = itoa(-12345, str, 10);
  ASSERT_STREQ("-12345", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_FiveDigitNegativeIntegerTest2) {
  char *str=NULL;
  str = itoa(-12340, str, 10);
  ASSERT_STREQ("-12340", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_FiveDigitNegativeIntegerTest3) {
  char *str=NULL;
  str = itoa(-12305, str, 10);
  ASSERT_STREQ("-12305", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_FiveDigitNegativeIntegerTest4) {
  char *str=NULL;
  str = itoa(-12045, str, 10);
  ASSERT_STREQ("-12045", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_FiveDigitNegativeIntegerTest5) {
  char *str=NULL;
  str = itoa(-10345, str, 10);
  ASSERT_STREQ("-10345", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_SixDigitNegativeIntegerTest1) {
  char *str=NULL;
  str = itoa(-123456, str, 10);
  ASSERT_STREQ("-123456", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_SixDigitNegativeIntegerTest2) {
  char *str=NULL;
  str = itoa(-123450, str, 10);
  ASSERT_STREQ("-123450", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_SixDigitNegativeIntegerTest3) {
  char *str=NULL;
  str = itoa(-123406, str, 10);
  ASSERT_STREQ("-123406", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_SixDigitNegativeIntegerTest4) {
  char *str=NULL;
  str = itoa(-123056, str, 10);
  ASSERT_STREQ("-123056", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_SixDigitNegativeIntegerTest5) {
  char *str=NULL;
  str = itoa(-120456, str, 10);
  ASSERT_STREQ("-120456", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_SixDigitNegativeIntegerTest6) {
  char *str=NULL;
  str = itoa(-103456, str, 10);
  ASSERT_STREQ("-103456", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_SevenDigitNegativeIntegerTest1) {
  char *str=NULL;
  str = itoa(-1234567, str, 10);
  ASSERT_STREQ("-1234567", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_SevenDigitNegativeIntegerTest2) {
  char *str=NULL;
  str = itoa(-1234560, str, 10);
  ASSERT_STREQ("-1234560", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_SevenDigitNegativeIntegerTest3) {
  char *str=NULL;
  str = itoa(-1234507, str, 10);
  ASSERT_STREQ("-1234507", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_SevenDigitNegativeIntegerTest4) {
  char *str=NULL;
  str = itoa(-1234067, str, 10);
  ASSERT_STREQ("-1234067", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_SevenDigitNegativeIntegerTest5) {
  char *str=NULL;
  str = itoa(-1230567, str, 10);
  ASSERT_STREQ("-1230567", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_SevenDigitNegativeIntegerTest6) {
  char *str=NULL;
  str = itoa(-1204567, str, 10);
  ASSERT_STREQ("-1204567", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_SevenDigitNegativeIntegerTest7) {
  char *str=NULL;
  str = itoa(-1034567, str, 10);
  ASSERT_STREQ("-1034567", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_EightDigitNegativeIntegerTest1) {
  char *str=NULL;
  str = itoa((int)-12345678, str, 10);
  ASSERT_STREQ("-12345678", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_EightDigitNegativeIntegerTest2) {
  char *str=NULL;
  str = itoa((int)-12345670, str, 10);
  ASSERT_STREQ("-12345670", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_EightDigitNegativeIntegerTest3) {
  char *str=NULL;
  str = itoa((int)-12345608, str, 10);
  ASSERT_STREQ("-12345608", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_EightDigitNegativeIntegerTest4) {
  char *str=NULL;
  str = itoa((int)-12345078, str, 10);
  ASSERT_STREQ("-12345078", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_EightDigitNegativeIntegerTest5) {
  char *str=NULL;
  str = itoa((int)-12340678, str, 10);
  ASSERT_STREQ("-12340678", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_EightDigitNegativeIntegerTest6) {
  char *str=NULL;
  str = itoa((int)-12305678, str, 10);
  ASSERT_STREQ("-12305678", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_EightDigitNegativeIntegerTest7) {
  char *str=NULL;
  str = itoa((int)-12045678, str, 10);
  ASSERT_STREQ("-12045678", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_EightDigitNegativeIntegerTest8) {
  char *str=NULL;
  str = itoa((int)-10345678, str, 10);
  ASSERT_STREQ("-10345678", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_NineDigitNegativeIntegerTest1) {
  char *str=NULL;
  str = itoa((int)-123456789, str, 10);
  ASSERT_STREQ("-123456789", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_NineDigitNegativeIntegerTest2) {
  char *str=NULL;
  str = itoa((int)-123456780, str, 10);
  ASSERT_STREQ("-123456780", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_NineDigitNegativeIntegerTest3) {
  char *str=NULL;
  str = itoa((int)-123456709, str, 10);
  ASSERT_STREQ("-123456709", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_NineDigitNegativeIntegerTest4) {
  char *str=NULL;
  str = itoa((int)-123456089, str, 10);
  ASSERT_STREQ("-123456089", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_NineDigitNegativeIntegerTest5) {
  char *str=NULL;
  str = itoa((int)-123450789, str, 10);
  ASSERT_STREQ("-123450789", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_NineDigitNegativeIntegerTest6) {
  char *str=NULL;
  str = itoa((int)-123406789, str, 10);
  ASSERT_STREQ("-123406789", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_NineDigitNegativeIntegerTest7) {
  char *str=NULL;
  str = itoa((int)-123056789, str, 10);
  ASSERT_STREQ("-123056789", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_NineDigitNegativeIntegerTest8) {
  char *str=NULL;
  str = itoa((int)-120456789, str, 10);
  ASSERT_STREQ("-120456789", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_NineDigitNegativeIntegerTest9) {
  char *str=NULL;
  str = itoa((int)-103456789, str, 10);
  ASSERT_STREQ("-103456789", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_TenDigitNegativeIntegerTest1) {
  char *str=NULL;
  str = itoa((int)-1234567891, str, 10);
  ASSERT_STREQ("-1234567891", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_TenDigitNegativeIntegerTest2) {
  char *str=NULL;
  str = itoa((int)-1234567890, str, 10);
  ASSERT_STREQ("-1234567890", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_TenDigitNegativeIntegerTest3) {
  char *str=NULL;
  str = itoa((int)-1234567801, str, 10);
  ASSERT_STREQ("-1234567801", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_TenDigitNegativeIntegerTest4) {
  char *str=NULL;
  str = itoa((int)-1234567091, str, 10);
  ASSERT_STREQ("-1234567091", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_TenDigitNegativeIntegerTest5) {
  char *str=NULL;
  str = itoa((int)-1234560891, str, 10);
  ASSERT_STREQ("-1234560891", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_TenDigitNegativeIntegerTest6) {
  char *str=NULL;
  str = itoa((int)-1234507891, str, 10);
  ASSERT_STREQ("-1234507891", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_TenDigitNegativeIntegerTest7) {
  char *str=NULL;
  str = itoa((int)-1234067891, str, 10);
  ASSERT_STREQ("-1234067891", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_TenDigitNegativeIntegerTest8) {
  char *str=NULL;
  str = itoa((int)-1230567891, str, 10);
  ASSERT_STREQ("-1230567891", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_TenDigitNegativeIntegerTest9) {
  char *str=NULL;
  str = itoa((int)-1204567891, str, 10);
  ASSERT_STREQ("-1204567891", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base10_TenDigitNegativeIntegerTest10) {
  char *str=NULL;
  str = itoa((int)-1034567891, str, 10);
  ASSERT_STREQ("-1034567891", str);
  HEX_FREE(str);
}

/***********************************
 * itoa Base 2
 * *********************************/

TEST(itoaTest, Base2_PositiveIntegerTest1) {
  char *str=NULL;
  str = itoa((int)0, str, 2);
  ASSERT_STREQ("0", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base2_PositiveIntegerTest2) {
  char *str=NULL;
  str = itoa((int)1, str, 2);
  ASSERT_STREQ("1", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base2_PositiveIntegerTest3) {
  char *str=NULL;
  str = itoa((int)2, str, 2);
  ASSERT_STREQ("10", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base2_PositiveIntegerTest4) {
  char *str=NULL;
  str = itoa((int)4, str, 2);
  ASSERT_STREQ("100", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base2_PositiveIntegerTest5) {
  char *str=NULL;
  str = itoa((int)7, str, 2);
  ASSERT_STREQ("111", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base2_PositiveIntegerTest6) {
  char *str=NULL;
  str = itoa((int)512, str, 2);
  ASSERT_STREQ("1000000000", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base2_PositiveIntegerTest7) {
  char *str=NULL;
  str = itoa((int)1024, str, 2);
  ASSERT_STREQ("10000000000", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base2_PositiveIntegerTest8) {
  char *str=NULL;
  str = itoa((int)(1024+512), str, 2);
  ASSERT_STREQ("11000000000", str);
  HEX_FREE(str);
}

/***********************************
 * itoa Base 8
 * *********************************/
TEST(itoaTest, Base8_PositiveIntegerTest1) {
  char *str=NULL;
  str = itoa((int)7, str, 8);
  ASSERT_STREQ("7", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base8_PositiveIntegerTest2) {
  char *str=NULL;
  str = itoa((int)8, str, 8);
  ASSERT_STREQ("10", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base8_PositiveIntegerTest3) {
  char *str=NULL;
  str = itoa((int)15, str, 8);
  ASSERT_STREQ("17", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base8_PositiveIntegerTest4) {
  char *str=NULL;
  str = itoa((int)16, str, 8);
  ASSERT_STREQ("20", str);
  HEX_FREE(str);
}

TEST(itoaTest, Base8_PositiveIntegerTest5) {
  char *str=NULL;
  str = itoa((int)64, str, 8);
  ASSERT_STREQ("100", str);
  HEX_FREE(str);
}

/*******************************************************************************
 * Test for:
 * int atoi(const char * str);
 ******************************************************************************/
TEST(atoiTest, NullStringTest) {
  ASSERT_EQ(0, atoi(NULL));
}

TEST(atoiTest, ZeroStringTest) {
  ASSERT_EQ(0, atoi("0"));
}

TEST(atoiTest, ValidOneDigitPositiveIntegerTest1) {
  ASSERT_EQ(1, atoi("1"));
}

TEST(atoiTest, ValidOneDigitPositiveIntegerTest2) {
  ASSERT_EQ(9, atoi("9"));
}

TEST(atoiTest, ValidTwoDigitPositiveIntegerTest1) {
  ASSERT_EQ(12, atoi("12"));
}

TEST(atoiTest, ValidTwoDigitPositiveIntegerTest2) {
  ASSERT_EQ(10, atoi("+10"));
}

TEST(atoiTest, ValidTwoDigitPositiveIntegerTest3) {
  ASSERT_EQ(88, atoi("88"));
}

TEST(atoiTest, ValidTwoDigitPositiveIntegerTest4) {
  ASSERT_EQ(55, atoi("+55"));
}

TEST(atoiTest, ValidThreeDigitPositiveIntegerTest1) {
  ASSERT_EQ(123, atoi("+123"));
}

TEST(atoiTest, ValidThreeDigitPositiveIntegerTest2) {
  ASSERT_EQ(120, atoi("120"));
}

TEST(atoiTest, ValidThreeDigitPositiveIntegerTest3) {
  ASSERT_EQ(103, atoi("103"));
}

TEST(atoiTest, ValidFourDigitPositiveIntegerTest1) {
  ASSERT_EQ(1234, atoi("1234"));
}

TEST(atoiTest, ValidFourDigitPositiveIntegerTest2) {
  ASSERT_EQ(1230, atoi("+1230"));
}

TEST(atoiTest, ValidFourDigitPositiveIntegerTest3) {
  ASSERT_EQ(1204, atoi("1204"));
}

TEST(atoiTest, ValidFourDigitPositiveIntegerTest4) {
  ASSERT_EQ(1034, atoi("+1034"));
}

TEST(atoiTest, ValidFiveDigitPositiveIntegerTest1) {
  ASSERT_EQ(12345, atoi("+12345"));
}

TEST(atoiTest, ValidFiveDigitPositiveIntegerTest2) {
  ASSERT_EQ(12340, atoi("12340"));
}

TEST(atoiTest, ValidFiveDigitPositiveIntegerTest3) {
  ASSERT_EQ(12305, atoi("+12305"));
}

TEST(atoiTest, ValidFiveDigitPositiveIntegerTest4) {
  ASSERT_EQ(12045, atoi("12045"));
}

TEST(atoiTest, ValidFiveDigitPositiveIntegerTest5) {
  ASSERT_EQ(10345, atoi("10345"));
}

TEST(atoiTest, ValidSixDigitPositiveIntegerTest1) {
  ASSERT_EQ(123456, atoi("+123456"));
}

TEST(atoiTest, ValidSixDigitPositiveIntegerTest2) {
  ASSERT_EQ(123450, atoi("123450"));
}

TEST(atoiTest, ValidSixDigitPositiveIntegerTest3) {
  ASSERT_EQ(123406, atoi("+123406"));
}

TEST(atoiTest, ValidSixDigitPositiveIntegerTest4) {
  ASSERT_EQ(123056, atoi("+123056"));
}

TEST(atoiTest, ValidSixDigitPositiveIntegerTest5) {
  ASSERT_EQ(120456, atoi("+120456"));
}

TEST(atoiTest, ValidSixDigitPositiveIntegerTest6) {
  ASSERT_EQ(103456, atoi("+103456"));
}

TEST(atoiTest, ValidSevenDigitPositiveIntegerTest1) {
  ASSERT_EQ(1234567, atoi("+1234567"));
}

TEST(atoiTest, ValidSevenDigitPositiveIntegerTest2) {
  ASSERT_EQ(1234560, atoi("1234560"));
}

TEST(atoiTest, ValidSevenDigitPositiveIntegerTest3) {
  ASSERT_EQ(1234507, atoi("+1234507"));
}

TEST(atoiTest, ValidSevenDigitPositiveIntegerTest4) {
  ASSERT_EQ(1234067, atoi("+1234067"));
}

TEST(atoiTest, ValidSevenDigitPositiveIntegerTest5) {
  ASSERT_EQ(1230567, atoi("+1230567"));
}

TEST(atoiTest, ValidSevenDigitPositiveIntegerTest6) {
  ASSERT_EQ(1204567, atoi("1204567"));
}

TEST(atoiTest, ValidSevenDigitPositiveIntegerTest7) {
  ASSERT_EQ(1234567, atoi("+1234567"));
}

TEST(atoiTest, ValidEightDigitPositiveIntegerTest1) {
  ASSERT_EQ(12345678, atoi("+12345678"));
}

TEST(atoiTest, ValidEightDigitPositiveIntegerTest2) {
  ASSERT_EQ(12345670, atoi("12345670"));
}

TEST(atoiTest, ValidEightDigitPositiveIntegerTest3) {
  ASSERT_EQ(12345608, atoi("+12345608"));
}

TEST(atoiTest, ValidEightDigitPositiveIntegerTest4) {
  ASSERT_EQ(12345078, atoi("12345078"));
}

TEST(atoiTest, ValidEightDigitPositiveIntegerTest5) {
  ASSERT_EQ(12340678, atoi("+12340678"));
}

TEST(atoiTest, ValidEightDigitPositiveIntegerTest6) {
  ASSERT_EQ(12305678, atoi("+12305678"));
}

TEST(atoiTest, ValidEightDigitPositiveIntegerTest7) {
  ASSERT_EQ(12045678, atoi("12045678"));
}

TEST(atoiTest, ValidEightDigitPositiveIntegerTest8) {
  ASSERT_EQ(10345678, atoi("+10345678"));
}

TEST(atoiTest, ValidNineDigitPositiveIntegerTest1) {
  ASSERT_EQ(123456789, atoi("+123456789"));
}

TEST(atoiTest, ValidNineDigitPositiveIntegerTest2) {
  ASSERT_EQ(123456780, atoi("123456780"));
}

TEST(atoiTest, ValidNineDigitPositiveIntegerTest3) {
  ASSERT_EQ(123456709, atoi("+123456709"));
}

TEST(atoiTest, ValidNineDigitPositiveIntegerTest4) {
  ASSERT_EQ(123456089, atoi("123456089"));
}

TEST(atoiTest, ValidNineDigitPositiveIntegerTest5) {
  ASSERT_EQ(123450789, atoi("+123450789"));
}

TEST(atoiTest, ValidNineDigitPositiveIntegerTest6) {
  ASSERT_EQ(123406789, atoi("123406789"));
}

TEST(atoiTest, ValidNineDigitPositiveIntegerTest7) {
  ASSERT_EQ(123056789, atoi("+123056789"));
}

TEST(atoiTest, ValidNineDigitPositiveIntegerTest8) {
  ASSERT_EQ(120456789, atoi("120456789"));
}

TEST(atoiTest, ValidNineDigitPositiveIntegerTest9) {
  ASSERT_EQ(103456789, atoi("+103456789"));
}

TEST(atoiTest, ValidTenDigitPositiveIntegerTest1) {
  ASSERT_EQ(1234567891, atoi("+1234567891"));
}

TEST(atoiTest, ValidTenDigitPositiveIntegerTest2) {
  ASSERT_EQ(1234567890, atoi("1234567890"));
}

TEST(atoiTest, ValidTenDigitPositiveIntegerTest3) {
  ASSERT_EQ(1234567801, atoi("+1234567801"));
}

TEST(atoiTest, ValidTenDigitPositiveIntegerTest4) {
  ASSERT_EQ(1234567091, atoi("1234567091"));
}

TEST(atoiTest, ValidTenDigitPositiveIntegerTest5) {
  ASSERT_EQ(1234560891, atoi("+1234560891"));
}

TEST(atoiTest, ValidTenDigitPositiveIntegerTest6) {
  ASSERT_EQ(1234507891, atoi("1234507891"));
}

TEST(atoiTest, ValidTenDigitPositiveIntegerTest7) {
  ASSERT_EQ(1234067891, atoi("+1234067891"));
}

TEST(atoiTest, ValidTenDigitPositiveIntegerTest8) {
  ASSERT_EQ(1230567891, atoi("1230567891"));
}

TEST(atoiTest, ValidTenDigitPositiveIntegerTest9) {
  ASSERT_EQ(1204567891, atoi("+1204567891"));
}

TEST(atoiTest, ValidTenDigitPositiveIntegerTest10) {
  ASSERT_EQ(1034567891, atoi("1034567891"));
}

TEST(atoiTest, ValidOneDigitNegativeIntegerTest1) {
  ASSERT_EQ(-1, atoi("-1"));
}

TEST(atoiTest, ValidOneDigitNegativeIntegerTest2) {
  ASSERT_EQ(-9, atoi("-9"));
}

TEST(atoiTest, ValidTwoDigitNegativeIntegerTest1) {
  ASSERT_EQ(-21, atoi("-21"));
}

TEST(atoiTest, ValidTwoDigitNegativeIntegerTest2) {
  ASSERT_EQ(-20, atoi("-20"));
}

TEST(atoiTest, ValidThreeDigitNegativeIntegerTest1) {
  ASSERT_EQ(-321, atoi("-321"));
}

TEST(atoiTest, ValidThreeDigitNegativeIntegerTest2) {
  ASSERT_EQ(-320, atoi("-320"));
}

TEST(atoiTest, ValidThreeDigitNegativeIntegerTest3) {
  ASSERT_EQ(-301, atoi("-301"));
}

TEST(atoiTest, ValidFourDigitNegativeIntegerTest1) {
  ASSERT_EQ(-4321, atoi("-4321"));
}

TEST(atoiTest, ValidFourDigitNegativeIntegerTest2) {
  ASSERT_EQ(-4320, atoi("-4320"));
}

TEST(atoiTest, ValidFourDigitNegativeIntegerTest3) {
  ASSERT_EQ(-4301, atoi("-4301"));
}

TEST(atoiTest, ValidFourDigitNegativeIntegerTest4) {
  ASSERT_EQ(-4021, atoi("-4021"));
}

TEST(atoiTest, ValidFiveDigitNegativeIntegerTest1) {
  ASSERT_EQ(-54321, atoi("-54321"));
}

TEST(atoiTest, ValidFiveDigitNegativeIntegerTest2) {
  ASSERT_EQ(-54320, atoi("-54320"));
}

TEST(atoiTest, ValidFiveDigitNegativeIntegerTest3) {
  ASSERT_EQ(-54301, atoi("-54301"));
}

TEST(atoiTest, ValidFiveDigitNegativeIntegerTest4) {
  ASSERT_EQ(-54021, atoi("-54021"));
}

TEST(atoiTest, ValidFiveDigitNegativeIntegerTest5) {
  ASSERT_EQ(-50321, atoi("-50321"));
}

TEST(atoiTest, ValidSixDigitNegativeIntegerTest1) {
  ASSERT_EQ(-654321, atoi("-654321"));
}

TEST(atoiTest, ValidSixDigitNegativeIntegerTest2) {
  ASSERT_EQ(-654320, atoi("-654320"));
}

TEST(atoiTest, ValidSixDigitNegativeIntegerTest3) {
  ASSERT_EQ(-654301, atoi("-654301"));
}

TEST(atoiTest, ValidSixDigitNegativeIntegerTest4) {
  ASSERT_EQ(-654021, atoi("-654021"));
}

TEST(atoiTest, ValidSixDigitNegativeIntegerTest5) {
  ASSERT_EQ(-650321, atoi("-650321"));
}

TEST(atoiTest, ValidSixDigitNegativeIntegerTest6) {
  ASSERT_EQ(-604321, atoi("-604321"));
}

TEST(atoiTest, ValidSevenDigitNegativeIntegerTest1) {
  ASSERT_EQ(-7654321, atoi("-7654321"));
}

TEST(atoiTest, ValidSevenDigitNegativeIntegerTest2) {
  ASSERT_EQ(-7654320, atoi("-7654320"));
}

TEST(atoiTest, ValidSevenDigitNegativeIntegerTest3) {
  ASSERT_EQ(-7654301, atoi("-7654301"));
}

TEST(atoiTest, ValidSevenDigitNegativeIntegerTest4) {
  ASSERT_EQ(-7654021, atoi("-7654021"));
}

TEST(atoiTest, ValidSevenDigitNegativeIntegerTest5) {
  ASSERT_EQ(-7650321, atoi("-7650321"));
}

TEST(atoiTest, ValidSevenDigitNegativeIntegerTest6) {
  ASSERT_EQ(-7604321, atoi("-7604321"));
}

TEST(atoiTest, ValidSevenDigitNegativeIntegerTest7) {
  ASSERT_EQ(-7054321, atoi("-7054321"));
}

TEST(atoiTest, ValidEightDigitNegativeIntegerTest1) {
  ASSERT_EQ(-87654321, atoi("-87654321"));
}

TEST(atoiTest, ValidEightDigitNegativeIntegerTest2) {
  ASSERT_EQ(-87654320, atoi("-87654320"));
}

TEST(atoiTest, ValidEightDigitNegativeIntegerTest3) {
  ASSERT_EQ(-87654301, atoi("-87654301"));
}

TEST(atoiTest, ValidEightDigitNegativeIntegerTest4) {
  ASSERT_EQ(-87654021, atoi("-87654021"));
}

TEST(atoiTest, ValidEightDigitNegativeIntegerTest5) {
  ASSERT_EQ(-87650321, atoi("-87650321"));
}

TEST(atoiTest, ValidEightDigitNegativeIntegerTest6) {
  ASSERT_EQ(-87604321, atoi("-87604321"));
}

TEST(atoiTest, ValidEightDigitNegativeIntegerTest7) {
  ASSERT_EQ(-87054321, atoi("-87054321"));
}

TEST(atoiTest, ValidEightDigitNegativeIntegerTest8) {
  ASSERT_EQ(-80654321, atoi("-80654321"));
}

TEST(atoiTest, ValidNineDigitNegativeIntegerTest1) {
  ASSERT_EQ(-987654321, atoi("-987654321"));
}

TEST(atoiTest, ValidNineDigitNegativeIntegerTest2) {
  ASSERT_EQ(-987654320, atoi("-987654320"));
}

TEST(atoiTest, ValidNineDigitNegativeIntegerTest3) {
  ASSERT_EQ(-987654301, atoi("-987654301"));
}

TEST(atoiTest, ValidNineDigitNegativeIntegerTest4) {
  ASSERT_EQ(-987654021, atoi("-987654021"));
}

TEST(atoiTest, ValidNineDigitNegativeIntegerTest5) {
  ASSERT_EQ(-987650321, atoi("-987650321"));
}

TEST(atoiTest, ValidNineDigitNegativeIntegerTest6) {
  ASSERT_EQ(-987604321, atoi("-987604321"));
}

TEST(atoiTest, ValidNineDigitNegativeIntegerTest7) {
  ASSERT_EQ(-987054321, atoi("-987054321"));
}

TEST(atoiTest, ValidNineDigitNegativeIntegerTest8) {
  ASSERT_EQ(-980654321, atoi("-980654321"));
}

TEST(atoiTest, ValidNineDigitNegativeIntegerTest9) {
  ASSERT_EQ(-907654321, atoi("-907654321"));
}

TEST(atoiTest, ValidTenDigitNegativeIntegerTest1) {
  ASSERT_EQ(-1987654321, atoi("-1987654321"));
}

TEST(atoiTest, ValidTenDigitNegativeIntegerTest2) {
  ASSERT_EQ(-1987654320, atoi("-1987654320"));
}

TEST(atoiTest, ValidTenDigitNegativeIntegerTest3) {
  ASSERT_EQ(-1987654301, atoi("-1987654301"));
}

TEST(atoiTest, ValidTenDigitNegativeIntegerTest4) {
  ASSERT_EQ(-1987654021, atoi("-1987654021"));
}

TEST(atoiTest, ValidTenDigitNegativeIntegerTest5) {
  ASSERT_EQ(-1987650321, atoi("-1987650321"));
}

TEST(atoiTest, ValidTenDigitNegativeIntegerTest6) {
  ASSERT_EQ(-1987604321, atoi("-1987604321"));
}

TEST(atoiTest, ValidTenDigitNegativeIntegerTest7) {
  ASSERT_EQ(-1987054321, atoi("-1987054321"));
}

TEST(atoiTest, ValidTenDigitNegativeIntegerTest8) {
  ASSERT_EQ(-1980654321, atoi("-1980654321"));
}

TEST(atoiTest, ValidTenDigitNegativeIntegerTest9) {
  ASSERT_EQ(-1907654321, atoi("-1907654321"));
}

TEST(atoiTest, ValidTenDigitNegativeIntegerTest10) {
  ASSERT_EQ(-1087654321, atoi("-1087654321"));
}

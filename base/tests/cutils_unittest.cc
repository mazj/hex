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
  ASSERT_EQ(10, atoi("10"));
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
  ASSERT_EQ(670, atoi("+670"));
}

TEST(atoiTest, ValidThreeDigitPositiveIntegerTest3) {
  ASSERT_EQ(880, atoi("880"));
}

TEST(atoiTest, ValidFourDigitPositiveIntegerTest1) {
  ASSERT_EQ(1234, atoi("1234"));
}

TEST(atoiTest, ValidFourDigitPositiveIntegerTest2) {
  ASSERT_EQ(9876, atoi("+9876"));
}

TEST(atoiTest, ValidFourDigitPositiveIntegerTest3) {
  ASSERT_EQ(1000, atoi("1000"));
}

TEST(atoiTest, ValidFiveDigitPositiveIntegerTest1) {
  ASSERT_EQ(10000, atoi("+10000"));
}

TEST(atoiTest, ValidFiveDigitPositiveIntegerTest2) {
  ASSERT_EQ(99999, atoi("99999"));
}

TEST(atoiTest, ValidFiveDigitPositiveIntegerTest3) {
  ASSERT_EQ(12345, atoi("+12345"));
}

TEST(atoiTest, ValidFiveDigitPositiveIntegerTest4) {
  ASSERT_EQ(10000, atoi("+10000"));
}

TEST(atoiTest, ValidTwoDigitNegativeIntegerTest1) {
  ASSERT_EQ(-12, atoi("-12"));
}

TEST(atoiTest, ValidTwoDigitNegativeIntegerTest2) {
  ASSERT_EQ(-20, atoi("-20"));
}

TEST(atoiTest, ValidTwoDigitNegativeIntegerTest3) {
  ASSERT_EQ(-88, atoi("-88"));
}

#include "../strutils.h"
#include "../unittest.h"

#include <string.h>

TEST(StrToUpperTest, NullInputTest) {
  EXPECT_EQ(NULL, strtoupper(NULL));
}

TEST(StrToUpperTest, ValidSingleWordTest) {
  char s[] = "test";
  ASSERT_STREQ("TEST", strtoupper(s));
}

TEST(strtolowerTest, NULLInputTest) {
 EXPECT_EQ(NULL, strtolower(NULL));
}

TEST(strtolowerTest, ValidSingleWordTest) {
  char s[] = "TEST"; 
  ASSERT_STREQ("test", strtolower(s));
}

#include "unittest.h"
#include "utils.h"

TEST(MaxTest, MaxOfPositiveInteger) {
  EXPECT_EQ(6, MAX(5,6));
}

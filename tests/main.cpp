#include "gtest/gtest.h"
#include "longnumber.hpp"

using namespace longnumber;

TEST(MathTest, AddTest) {
  EXPECT_EQ(2.0_longnum, LongNumber(2) + LongNumber(0));
  EXPECT_EQ(0._longnum, LongNumber(2) + LongNumber(-2));
  EXPECT_EQ(-4._longnum, LongNumber(-2) + LongNumber(-2));
}

TEST(MathTest, DifTest) {
  EXPECT_EQ(2.0_longnum, LongNumber(2) - LongNumber(0));
  EXPECT_EQ(4.0_longnum, LongNumber(2) - LongNumber(-2));
  EXPECT_EQ(0._longnum, -(LongNumber(-2) - LongNumber(-2)));
}

TEST(MathTest, MulTest) {
  EXPECT_EQ(0.0_longnum, LongNumber(2) * LongNumber(0));
  EXPECT_EQ(0.4_longnum, LongNumber(2) * LongNumber(0.2));
  EXPECT_EQ(4.0_longnum, LongNumber(-2) * LongNumber(-2));
}

TEST(MathTest, DivTest) {
  LongNumber::rounding_pos=3;
  EXPECT_EQ(0.2_longnum, LongNumber(2) / LongNumber(10));
  EXPECT_EQ("0.333", (LongNumber(1) / LongNumber(3)).get_decimal());
  EXPECT_EQ(4.0_longnum, LongNumber(-2) * LongNumber(-2));
}

TEST(MathTest, LessBiggerEqTest) {
  EXPECT_EQ(true, LongNumber(2) < LongNumber(10));
  EXPECT_EQ(false, LongNumber(1) > LongNumber(3));
  EXPECT_EQ(true, LongNumber(-2) == -LongNumber(2));
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
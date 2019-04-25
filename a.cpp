#include "gtest/gtest.h"

int cubic(int c) {
  return c * c * c;
}

TEST(testMath, myCubeTest)
{
    EXPECT_EQ(1000, cubic(10));
    EXPECT_EQ(1000, cubic(3));
    EXPECT_EQ("abc", std::string("ab") + "c");
    EXPECT_EQ("abcd", std::string("ab") + "c");
}

// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }

// return sum of [l, r]
// long long rangesum(long long l, long long r) {
//   return (r + l) * (r - l + 1);
// }

// class MyTest : public ::testing::Test {
// protected:
//   virtual void SetUp() {
//     dat = 2.0;
//   }
//   double dat;
// };
//
// TEST_F(MyTest, FunctionTest) {
//   ASSERT_EQ(3, 1 + 2);
// }
//
// int main() {
//   return 0;
// }

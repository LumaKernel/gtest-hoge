#include "../src/rangesum.cpp"
#include "gtest/gtest.h"

long long naive(long long l, long long r, long long step = 1) {
  long long sum = 0;
  for(long long i = l; l <= r; i += step) sum += i;
  return sum;
}

TEST(RangeSum, Small) {
  EXPECT_EQ(rangesum(1, 5), 15);
  EXPECT_EQ(rangesum(0, 10), 55);
  EXPECT_EQ(rangesum(1, 10), 55);
  EXPECT_EQ(rangesum(3, 30), 462);
}

TEST(RangeSum, SmallWithSteps) {
  EXPECT_EQ(rangesum(1, 5, 2), 1 + 3 + 5);
  EXPECT_EQ(rangesum(1, 8, 2), 1 + 3 + 5 + 7);
}

TEST(RangeSum, Medium) {
  EXPECT_EQ(rangesum(0, 10), 55);
  EXPECT_EQ(rangesum(1, 10), 55);
  EXPECT_EQ(rangesum(3, 30), 462);
}

TEST(RangeSum, Large) {
  EXPECT_EQ(rangesum(1000, 100000), naive(1000, 100000));
}



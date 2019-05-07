#include "../src/rangesum.cpp"
#include "gtest/gtest.h"

TEST(RangeSum, Small) {
  EXPECT_EQ(rangesum(1, 5), 15);
  EXPECT_EQ(rangesum(0, 10), 55);
  EXPECT_EQ(rangesum(1, 10), 55);
  EXPECT_EQ(rangesum(3, 30), 462);

  EXPECT_EQ(rangesum(-4, 4), 0);
  EXPECT_EQ(rangesum(-11, 11), 0);
}

TEST(RangeSum, ZeroStep) {
  EXPECT_DEATH( rangesum(3, 5, 0) , "");
  EXPECT_DEATH( rangesum(92, -23, 0) , "");
}

TEST(RangeSum, SmallWithSteps) {
  EXPECT_EQ(rangesum(1, 5, 2), 1 + 3 + 5);
  EXPECT_EQ(rangesum(1, 8, 2), 1 + 3 + 5 + 7);
  EXPECT_EQ(rangesum(9, 1, -2), 9 + 7 + 5 + 3 + 1);
  EXPECT_EQ(rangesum(9, 2, -2), 9 + 7 + 5 + 3);
  EXPECT_EQ(rangesum(16, 11, -1), 16 + 15 + 14 + 13 + 12 + 11);
  EXPECT_EQ(rangesum(1, -17, -7), 1 + -6 + -13);

  EXPECT_EQ(rangesum(43, 20, 214), 43);

  EXPECT_EQ(rangesum(-5, 5, 2), 0);
  EXPECT_EQ(rangesum(-12, 12, 3), 0);
}

TEST(RangeSum, Large) {
  EXPECT_EQ(rangesum(1, 3000), 4501500);
  EXPECT_EQ(rangesum(-203, 49239), 1212243474ll);
  EXPECT_EQ(rangesum(-203, 49239, 17), 71314135);
  EXPECT_EQ(rangesum(23241, -12941, -3), 62126211);
  EXPECT_EQ(rangesum(20000, 100000), 4800060000ll);
  EXPECT_EQ(rangesum(450, 1000), 399475);
  EXPECT_EQ(rangesum(1525, 231451), 26783736376ll);
  EXPECT_EQ(rangesum(3333, 3333), 3333);

  long long X = 123456789123456789ll;
  EXPECT_EQ(rangesum(X, X), X);
  EXPECT_EQ(rangesum(X, X + 1), X + (X + 1));

  EXPECT_EQ(rangesum(-X, X), 0);
  EXPECT_EQ(rangesum(-X, X, X), 0);
  EXPECT_EQ(rangesum(X, -X, -1), 0);
  EXPECT_EQ(rangesum(-X, X, -3), -X);
  EXPECT_EQ(rangesum(-X, X + 1), X + 1);
  EXPECT_EQ(rangesum(-X, X + 1, X), 0);
}


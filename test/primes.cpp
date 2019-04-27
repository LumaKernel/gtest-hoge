#include "../src/primes.cpp"
#include "gtest/gtest.h"

TEST(Primes, SmallNumbers) {
  EXPECT_EQ(primes(1), std::vector<int>({}));
  EXPECT_EQ(primes(2), std::vector<int>({2}));
  EXPECT_EQ(primes(7), std::vector<int>({2, 3, 5, 7}));
  EXPECT_EQ(primes(10), std::vector<int>({2, 3, 5, 7}));
  EXPECT_EQ(primes(20), std::vector<int>({2, 3, 5, 7, 11, 13, 17, 19}));
}

TEST(Primes, BigNumbers) {
  // wolfram alpha で計算
  // ex : https://ja.wolframalpha.com/input/?i=10000%E4%BB%A5%E4%B8%8B%E3%81%AE%E7%B4%A0%E6%95%B0%E3%81%AE%E6%95%B0

  ASSERT_EQ(primes(1000).size(), 168);
  EXPECT_EQ(primes(1000).back(), 997);

  ASSERT_EQ(primes(10000).size(), 1229);
  EXPECT_EQ(primes(10000).back(), 9973);

  ASSERT_EQ(primes(100'000).size(), 9592);
  EXPECT_EQ(primes(100'000).back(), 99991);

  ASSERT_EQ(primes(1'000'000).size(), 78498);
  EXPECT_EQ(primes(1'000'000).back(), 999'983);
}


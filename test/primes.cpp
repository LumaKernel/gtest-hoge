#include "../src/primes.cpp"
#include "gtest/gtest.h"

TEST(PRIMES, enumerate_primes) {
  EXPECT_EQ((std::vector<int>{2, 3, 5, 7}), primes(10));
}


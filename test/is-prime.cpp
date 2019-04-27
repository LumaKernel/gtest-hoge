#include "../src/is-prime.cpp"
#include "gtest/gtest.h"

TEST(IsPrime, Primes) {
  EXPECT_TRUE(isPrime(2));
  EXPECT_TRUE(isPrime(7));
  EXPECT_TRUE(isPrime(101));
  EXPECT_TRUE(isPrime(1'000'000'007));
  EXPECT_TRUE(isPrime(1'000'000'009));
}

TEST(IsPrime, NotPrimes) {
  EXPECT_FALSE(isPrime(1));
  EXPECT_FALSE(isPrime(4));
  EXPECT_FALSE(isPrime(10));
  EXPECT_FALSE(isPrime(57));
  EXPECT_FALSE(isPrime(1333));
  EXPECT_FALSE(isPrime(1'000'000'008));
}


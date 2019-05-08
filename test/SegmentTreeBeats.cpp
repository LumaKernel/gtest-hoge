#include "../src/SegmentTreeBeats.cpp"

using namespace std;
#include "gtest/gtest.h"
#include <algorithm>

class BeatsTest : public ::testing::Test {
protected:
  virtual void SetUp() {
  }
  virtual void TearDown() {
  }
};

template<class T>
struct Naive {
  std::vector<T> data;
  Naive(int n, T initial = 0): data(n, initial) { }
  Naive(std::initializer_list<T> il): data(il.begin(), il.end()) { }
  void set(int i, T x) {
    data.at(i) = x;
  }
  T get(int i) {
    return data.at(i);
  }
  void select_min(int l, int r, T x) {
    for(int i = l; i < r; i++) data.at(i) = std::min(data.at(i), x);
  }
  void select_max(int l, int r, T x) {
    for(int i = l; i < r; i++) data.at(i) = std::max(data.at(i), x);
  }
  void set(int l, int r, T x) {
    for(int i = l; i < r; i++) data.at(i) = x;
  }
  void add(int l, int r, T x) {
    for(int i = l; i < r; i++) data.at(i) += x;
  }
  T sum(int l, int r) {
    T s(0);
    for(int i = l; i < r; i++) s += data.at(i);
    return s;
  }
  void clamp(int l, int r, T a, T b) {
    for(int i = l; i < r; i++) data.at(i) = min(max(data.at(i), a), b);
  }
};

TEST(AddInfinity, One) {
  EXPECT_EQ(add_inf<int>(400) + add_inf<int>(400), 800);
  EXPECT_EQ(add_inf<int>(400) * add_inf<int>(400), 400 * 400);

  EXPECT_EQ(add_inf<int>(add_inf<int>::positive_infinity) + add_inf<int>(400), add_inf<int>::positive_infinity);

  EXPECT_EQ(
      add_inf<int>(add_inf<int>::positive_infinity - 1) * add_inf<int>(0),
      0
      );

  EXPECT_EQ(
      add_inf<int>(0) * add_inf<int>(add_inf<int>::positive_infinity - 1),
      0
      );

  EXPECT_EQ(
      add_inf<int>(2'000'000'000) * add_inf<int>(add_inf<int>::positive_infinity),
      add_inf<int>::positive_infinity
      );
}

TEST(BeatsTest, Simple) {
  SegmentTreeBeats<add_inf<int>> a({7, 45, 2, 34, 23, 49 ,12 ,5});

  EXPECT_EQ(a.size(), 8);
  
  EXPECT_EQ(a.sum(2, 4), 36);
  EXPECT_EQ(a.sum(1, 5), 45 + 2 + 34 + 23);
  EXPECT_EQ(a.sum(0, 1), 7);
  EXPECT_EQ(a.sum(4, 4), 0);
  EXPECT_EQ(a.get(6), 12);
  
  a.select_min(1, 4, 10);
  // {7, 10, 2, 10, 23, 49 ,12 ,5}
  EXPECT_EQ(a.sum(2, 4), 12);
  EXPECT_EQ(a.sum(1, 5), 10 + 2 + 10 + 23);
  EXPECT_EQ(a.sum(0, 1), 7);
  EXPECT_EQ(a.sum(4, 4), 0);
  EXPECT_EQ(a.get(2), 2);
  EXPECT_EQ(a.get(3), 10);
  EXPECT_EQ(a.get(4), 23);
  
  a.select_max(3, 7, 13);
  a.set(0, 3);
  // {3, 10, 2, 13, 23, 49 ,13 ,5}
  EXPECT_EQ(a.sum(2, 4), 2 + 13);
  EXPECT_EQ(a.sum(1, 5), 10 + 2 + 13 + 23);
  EXPECT_EQ(a.sum(0, 1), 3);
  EXPECT_EQ(a.sum(4, 4), 0);
  EXPECT_EQ(a.get(6), 13);
  EXPECT_EQ(a.get(7), 5);

  a.set(3, 5);
  a.add(0, 7, -4);
  // {-1, 6, -2, 1, 19, 45 ,9 ,5}
  EXPECT_EQ(a.sum(2, 4), -1);
  EXPECT_EQ(a.sum(1, 5), 6 - 2 + 1 + 19);
  EXPECT_EQ(a.sum(0, 1), -1);
  EXPECT_EQ(a.sum(4, 4), 0);
  EXPECT_EQ(a.get(6), 9);
  EXPECT_EQ(a.get(7), 5);

}

class BeatsSuite : public ::testing::TestWithParam<std::tuple<size_t, int, int, int, std::vector<int>>> {};

int OPS ();

TEST_P(BeatsSuite, RandomMedium) {
  using value_type = long long;

  size_t seed;
  int n, q, r;
  vector<int> distribution;

  tie(seed, n, q, r, distribution) = GetParam();

  ASSERT_GT(static_cast<long long>(n) * q * r, 0);
  ASSERT_LT(static_cast<long long>(n), add_inf<value_type>::positive_infinity / q / r);

  Naive<add_inf<value_type>> naive(n);
  using Seg = SegmentTreeBeats<add_inf<value_type>>;
  Seg beats(n);

  mt19937 mt(seed);
  vector<int> ops;

  for(int i = 0; i < OPS(); i++) for(int j = 0; j < distribution[i]; j++) ops.push_back(i);

  uniform_int_distribution<int> rdop(0, ops.size() - 1);
  uniform_int_distribution<int> rdidx(0, n - 1);
  uniform_int_distribution<value_type> rdnum(-r, r);

  map<int, int> counts;

  for(int i = 0; i < q; i++) {
    int l = rdidx(mt), r = rdidx(mt);
    if(l > r) swap(l, r);
    r++;

    int l2 = rdnum(mt), r2 = rdnum(mt);
    if(l2 > r2) swap(l2, r2);

    value_type num = rdnum(mt);
    int op = ops[rdop(mt)];
    counts[op]++;
    switch(op) {
      case 0:
        // 0 : set
        naive.set(l, num);
        beats.set(l, num);
        break;
      case 1:
        // 1 : get
        ASSERT_EQ(naive.get(l), beats.get(l));
        break;
      case 2:
        // 2 : add
        naive.add(l, r, num);
        beats.add(l, r, num);
        break;
      case 3:
        // 3 : sum
        ASSERT_EQ(naive.sum(l, r), beats.sum(l, r)) << "\n"
          << "  n : " << n
          << "  q : " << q
          << "  q-id : " << i
          << "  range [" << l << ", " << r << ") "
          << "\n";
        break;
      case 4:
        // 4 : select_min
        naive.select_min(l, r, num);
        beats.select_min(l, r, num);
        break;
      case 5:
        // 5 : select_max
        naive.select_max(l, r, num);
        beats.select_max(l, r, num);
        break;
      case 6:
        // 6 : clamp
        naive.clamp(l, r, l2, r2);
        beats.clamp(l, r, l2, r2);
        break;
      case 7:
        // 7 : range_set
        naive.set(l, r, num);
        beats.set(l, r, num);
        break;
      default: FAIL() << "error";
    }
  }
  ASSERT_EQ(beats.size(), n);
}

int OPS() { return 8; }

// 0 : set
// 1 : get
// 2 : add
// 3 : sum
// 4 : select_min
// 5 : select_max
// 6 : clamp
// 7 : range_set

INSTANTIATE_TEST_CASE_P(one, BeatsSuite, ::testing::Combine(
    ::testing::Values(1333, 1640),
    ::testing::Values(1, 3, 40, 5000),
    ::testing::Values(2000),
    ::testing::Values(5000),
    ::testing::Values(
      vector<int>({2, 2, 3, 3, 1, 1, 1}),
      vector<int>({100, 100, 70, 70, 3, 3, 1})
      )
    )
  );

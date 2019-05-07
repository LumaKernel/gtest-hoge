
#if 0

セグ木Beats



1) add x
2) clamp [l, r]

3) add y
4) clamp [s, t]

=>

1) add x + y
2) clamp [max(l + y, s), min(r + y, t)]



#endif

// includes {{{
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<tuple>
#include<cmath>
#include<random>
#include<cassert>
#include<bitset>
#include<cstdlib>
// #include<deque>
// #include<multiset>
// #include<cstring>
// #include<bits/stdc++.h>
// }}}
// using namespace std;
// using ll = long long;

// #undef DEBUG
#define DEBUG
// DEBUG {{{
#include <array>
#include <deque>
#include <list>
#include <ostream>
#include <queue>
#include <stack>
#include <tuple>
#include <valarray>
#include <vector>
template < int n, class... T >
typename std::enable_if< (n >= sizeof...(T)) >::type __output_tuple(
    std::ostream &, std::tuple< T... > const &) {}
template < int n, class... T >
typename std::enable_if< (n < sizeof...(T)) >::type __output_tuple(
    std::ostream &os, std::tuple< T... > const &t) {
  os << (n == 0 ? "" : ", ") << std::get< n >(t);
  __output_tuple< n + 1 >(os, t);
}
template < class... T >
std::ostream &operator<<(std::ostream &os, std::tuple< T... > const &t) {
  os << "(";
  __output_tuple< 0 >(os, t);
  os << ")";
  return os;
}
template < class T, class U >
std::ostream &operator<<(std::ostream &os, std::pair< T, U > const &p) {
  os << "(" << p.first << ", " << p.second << ")";
  return os;
}
template < class T >
std::ostream &operator<<(std::ostream &os, const std::stack< T > &a) {
  os << "{";
  for(auto tmp = a; tmp.size(); tmp.pop())
    os << (a.size() == tmp.size() ? "" : ", ") << tmp.top();
  os << "}";
  return os;
}
template < class T, class Container, class Compare >
std::ostream &operator<<(std::ostream &os,
    std::priority_queue< T, Container, Compare > a) {
  os << "{ (top) ";
  while(a.size()) os << a.top() << (a.size() == 1 ? "" : ", "), a.pop();
  os << " }";
  return os;
}
template < class T, class Container >
std::ostream &operator<<(std::ostream &os, std::queue< T, Container > a) {
  os << "{ ";
  while(a.size()) os << a.front() << (a.size() == 1 ? "" : ", "), a.pop();
  os << " }";
  return os;
}
#ifdef DEBUG
#if !defined(DEBUG_OUT)
#define DEBUG_OUT std::cerr
#endif
#define dump(...)                                                                \
  [&]() {                                                                        \
    auto __debug_tap = std::make_tuple(__VA_ARGS__);                             \
    DEBUG_OUT << "[" << __LINE__ << "] " << #__VA_ARGS__ << " = " << __debug_tap \
    << std::endl;                                                      \
  }()
template < class T >
inline void dump2D(T &d, size_t sizey, size_t sizex) {
  for(size_t i = 0; i < sizey; i++) {
    DEBUG_OUT << "\t";
    for(size_t j = 0; j < sizex; j++)
      DEBUG_OUT << d[i][j] << (j + 1 == sizex ? "" : "\t");
    DEBUG_OUT << std::endl;
  }
}
template < class T >
inline void dump1D(T &d, size_t sizey) {
  for(size_t i = 0; i < sizey; i++) {
    DEBUG_OUT << d[i] << (i + 1 == sizey ? "" : " ");
  }
  DEBUG_OUT << std::endl;
}
template <
class T, class = typename std::iterator_traits< decltype(begin(T())) >::value_type,
      class = typename std::enable_if< !std::is_same< T, std::string >::value >::type >
      std::ostream &operator<<(std::ostream &os, const T &a) {
        os << "{";
        for(auto ite = begin(a); ite != end(a); ++ite)
          os << (ite == begin(a) ? "" : ", ") << *ite;
        os << "}";
        return os;
      }
#else
#define dump(...) (42)
#define dump2D(...) (42)
#define dump1D(...) (42)
template <
class T, class = typename std::iterator_traits< decltype(begin(T())) >::value_type,
      class = typename std::enable_if< !std::is_same< T, std::string >::value >::type >
      std::ostream &operator<<(std::ostream &os, const T &a) {
        for(auto ite = begin(a); ite != end(a); ++ite)
          os << (ite == begin(a) ? "" : " ") << *ite;
        return os;
      }
#endif
// }}}

namespace std {
  template<class X, class Y>
  class numeric_limits<std::pair<X, Y>> {
    static constexpr bool has_infinity = numeric_limits<X>::has_infinity && numeric_limits<Y>::has_infinity;
    static std::pair<X, Y> infinity() {
      return has_infinity ? std::pair<X, Y>(numeric_limits<X>::infinity() && numeric_limits<Y>::infinity()) : max();
    }
    static std::pair<X, Y> max() {
      return std::pair<X, Y>(
          numeric_limits<X>::has_infinity ? numeric_limits<X>::infinity() : numeric_limits<X>::max(),
          numeric_limits<Y>::has_infinity ? numeric_limits<Y>::infinity() : numeric_limits<Y>::max());
    }
    static std::pair<X, Y> min() {
      return std::pair<X, Y>(
          numeric_limits<X>::has_infinity ? -numeric_limits<X>::infinity() : numeric_limits<X>::min(),
          numeric_limits<Y>::has_infinity ? -numeric_limits<Y>::infinity() : numeric_limits<Y>::min());
    }
  };
}

/// --- SegmentTree Beats {{{ ///

template<class X>
struct add_inf {
  using underlying_set = X;
  X value;
  static const X positive_infinity = std::numeric_limits<X>::has_infinity ? std::numeric_limits<X>::infinity() : std::numeric_limits<X>::max();
  static const X negative_infinity = std::numeric_limits<X>::has_infinity ? -std::numeric_limits<X>::infinity() : std::numeric_limits<X>::min();
  operator X() { return value; }
  add_inf(const X &value = X()): value(value) { }
  X operator+(const add_inf &a) const {
    if(value == positive_infinity || a.value == positive_infinity) return positive_infinity;
    if(value == negative_infinity || a.value == negative_infinity) return negative_infinity;
    return value + a.value;
  }
  X operator-(const add_inf &a) const {
    if(value == positive_infinity || a.value == negative_infinity) return positive_infinity;
    if(value == negative_infinity || a.value == positive_infinity) return negative_infinity;
    return value - a.value;
  }
  X operator*(const add_inf &a) const {
    if(value == positive_infinity) return a.value < 0 ? negative_infinity : positive_infinity;
    if(value == negative_infinity) return a.value < 0 ? positive_infinity : negative_infinity;
    if(a.value == positive_infinity) return value < 0 ? negative_infinity : positive_infinity;
    if(a.value == negative_infinity) return value < 0 ? positive_infinity : negative_infinity;
    return value * a.value;
  }
  X operator/(const add_inf &a) const {
    if(a.value == positive_infinity || a.value == negative_infinity) return 0;
    if(value == positive_infinity) return a.value < 0 ? negative_infinity : positive_infinity;
    if(value == negative_infinity) return a.value < 0 ? positive_infinity : negative_infinity;
    if(a.value == 0) return value < 0 ? negative_infinity : positive_infinity;
    return value / a.value;
  }
  add_inf& operator+=(const add_inf &a) {
    return *this = *this + a;
  }
  add_inf& operator-=(const add_inf &a) {
    return *this = *this - a;
  }
  add_inf& operator*=(const add_inf &a) {
    return *this = *this * a;
  }
  add_inf& operator/=(const add_inf &a) {
    return *this = *this / a;
  }
  bool operator<(const add_inf &a) const {
    return value < a.value;
  }
  bool operator==(const add_inf &a) const {
    return value == a.value;
  }
  bool operator>(const add_inf &a) const {
    return a < *this;
  }
  bool operator<=(const add_inf &a) const {
    return !(a < *this);
  }
  bool operator>=(const add_inf &a) const {
    return !(*this < a);
  }
  bool operator!=(const add_inf &a) const {
    return value != a.value;
  }
  X operator-() const {
    if(value == positive_infinity) return negative_infinity;
    if(value == negative_infinity) return positive_infinity;
    return -value;
  }
  friend std::ostream& operator <<(std::ostream &os, const add_inf &a) {
    os << a.value;
    return os;
  }
};
template<class X>
const X add_inf<X>::positive_infinity;
template<class X>
const X add_inf<X>::negative_infinity;

template<class X>
struct SegmentTreeBeats {
public:
  using size_type = std::size_t;
  using index_type = long long;
  using underlying_set = typename X::underlying_set;
private:
  size_type n;
  size_type _size;
  std::vector<X> data;
  std::vector<X> max0;
  std::vector<X> max1;
  std::vector<X> min0;
  std::vector<X> min1;

  std::vector<size_type> cnt_max0;
  std::vector<size_type> cnt_min0;

  // laz
  // 1) add x
  std::vector<X> add;
  // 2) clamp [L, R]
  std::vector<X> L;
  std::vector<X> R;

  const X positive_infinity = X::positive_infinity;
  const X negative_infinity = X::negative_infinity;
  const underlying_set identity = underlying_set(0);
public:
  SegmentTreeBeats(size_type t, X initial = 0) {
    _reset(t, initial);
    for(size_type i = n - 1; i--; ) update(i);
  }
  template<class InputIter, class = typename std::iterator_traits<InputIter>::value_type>
  SegmentTreeBeats(InputIter first, InputIter last) {
    _reset(std::distance(first, last));
    for(std::size_t i = n - 1; first != last; ++i, ++first) {
      max0[i] = min0[i] = data[i] = *first;
    }
    for(std::size_t i = n - 1; i--; ) update(i);
  }
  template<class T>
  SegmentTreeBeats(std::initializer_list<T> il): SegmentTreeBeats(il.begin(), il.end()) { }
private:
  void _reset(size_type t, const X &initial = X(0)) {
    _size = t;
    n = 1;
    while(n < t) n <<= 1;
    data.resize(2 * n - 1, initial);
    max0.resize(2 * n - 1, initial);
    max1.resize(2 * n - 1, negative_infinity);
    min0.resize(2 * n - 1, initial);
    min1.resize(2 * n - 1, positive_infinity);
    cnt_max0.resize(2 * n - 1, 1);
    cnt_min0.resize(2 * n - 1, 1);
    add.resize(2 * n - 1, identity);
    L.resize(2 * n - 1, negative_infinity);
    R.resize(2 * n - 1, positive_infinity);
  }
private:
  // 0 < sz
  /*
1) add x
2) clamp [l, r]

3) add y
4) clamp [s, t]

=>

1) add x + y
2) clamp [clamp(l + y, [s, t]), clamp(r + y, [s, t])]
   */
  void eval(size_type k, size_type sz) {
    assert(sz > 0);
    data[k] += add[k] * static_cast<X>(sz);
    max0[k] += add[k];
    max1[k] += add[k];
    min0[k] += add[k];
    min1[k] += add[k];

    assert(L[k] <= R[k]);

    assert(max1[k] < R[k]);
    if(R[k] < max0[k]) {
      if(min1[k] == max0[k]) min1[k] = R[k];
      else if(min0[k] == max0[k]) min0[k] = R[k];
      data[k] -= (max0[k] - R[k]) * cnt_max0[k]; // TODO : 考察，ここの前提条件
      max0[k] = R[k];
    }
    assert(L[k] < min1[k]);
    if(min0[k] < L[k]) {
      if(max1[k] == min0[k]) max1[k] = L[k];
      else if(max0[k] == min0[k]) max0[k] = L[k];
      data[k] += (L[k] - min0[k]) * cnt_min0[k];
      min0[k] = L[k];
    }
    if(sz > 1) {
      add[2 * k + 1] += add[k]; // 可換則
      add[2 * k + 2] += add[k];
      L[2 * k + 1] = std::min<X>(std::max<X>(L[2 * k + 1] + add[k], L[k]), R[k]);
      R[2 * k + 1] = std::min<X>(std::max<X>(R[2 * k + 1] + add[k], L[k]), R[k]);
      L[2 * k + 2] = std::min<X>(std::max<X>(L[2 * k + 2] + add[k], L[k]), R[k]);
      R[2 * k + 2] = std::min<X>(std::max<X>(R[2 * k + 2] + add[k], L[k]), R[k]);
    }
    add[k] = identity;
    L[k] = negative_infinity;
    R[k] = positive_infinity;
  }
  void eval_down(size_type k, size_type sz) {
    assert(sz > 0);
    std::vector<size_type> v({k});
    while(k) v.emplace_back(--k >>= 1), sz <<= 1;
    while(v.size()) eval(v.back(), sz), sz >>= 1, v.pop_back();
  }
private:
  // range of k > 1
  void update_max(size_type k) {
    assert(k < n - 1);
    size_type cnt0 = cnt_max0[k * 2 + 1], cnt1 = cnt_max0[k * 2 + 2];
    X *v0 = &max0[k * 2 + 1],
    *v1 = &max0[k * 2 + 2],
    *v2 = &max1[k * 2 + 1],
    *v3 = &max1[k * 2 + 2];
    if(*v0 < *v1) std::swap(v0, v1), std::swap(cnt0, cnt1);
    if(*v1 < *v2) std::swap(v1, v2);
    if(*v1 < *v3) std::swap(v1, v3);
    max0[k] = *v0;
    max1[k] = *v1;
    if(*v0 == *v1) cnt0 += cnt1, max1[k] = std::max(*v2, *v3);
    cnt_max0[k] = cnt0;
  }
  // range of k > 1
  void update_min(size_type k) {
    assert(k < n - 1);
    size_type cnt0 = cnt_min0[k * 2 + 1], cnt1 = cnt_min0[k * 2 + 2];
    X *v0 = &min0[k * 2 + 1],
    *v1 = &min0[k * 2 + 2],
    *v2 = &min1[k * 2 + 1],
    *v3 = &min1[k * 2 + 2];
    if(*v1 < *v0) std::swap(v0, v1), std::swap(cnt0, cnt1);
    if(*v2 < *v1) std::swap(v1, v2);
    if(*v3 < *v1) std::swap(v1, v3);
    min0[k] = *v0;
    min1[k] = *v1;
    if(*v0 == *v1) cnt0 += cnt1, min1[k] = std::min(*v2, *v3);
    cnt_min0[k] = cnt0;
  }
  // range of k > 1
  // children must be evaled
  void update(size_type k) {
    update_min(k);
    update_max(k);
    data[k] = data[k * 2 + 1] + data[k * 2 + 2];
  }
  void update_up(size_type k) {
    assert(k >= n - 1);
    size_type sz = 1;
    while(k) --k >>= 1, eval(k * 2 + 1, sz), eval(k * 2 + 2, sz), update(k), sz <<= 1;
  }
public:
  void set(size_type i, X x) {
    assert(i < _size);
    i += n - 1;
    eval_down(i, 1);
    data[i] = max0[i] = min0[i] = x;
    update_up(i);
  }
  underlying_set get(size_type i) {
    assert(i < _size);
    i += n - 1;
    eval_down(i, 1);
    return data[i];
  }
  void set_positive_infinity(index_type l, index_type r) {
    select_max(l, r, positive_infinity);
  }
  void set_negative_infinity(index_type l, index_type r) {
    select_min(l, r, negative_infinity);
  }
  void select_min(index_type l, index_type r, const X& x) {
    if(l < 0) l = 0;
    if(r > static_cast<index_type>(_size)) r = _size;
    if(l >= r) return;
    select_min(l, r, x, 0, 0, n);
  }
  void select_max(index_type l, index_type r, const X& x) {
    if(l < 0) l = 0;
    if(r > static_cast<index_type>(_size)) r = _size;
    if(l >= r) return;
    select_max(l, r, x, 0, 0, n);
  }
private:
  void select_min(size_type a, size_type b, const X & x, size_type k, size_type l, size_type r) {
    eval(k, r - l);
    if(b <= l || r <= a || !(x < max0[k])) return;
    if(a <= l && r <= b && max1[k] < x) {
      R[k] = x;
      eval(k, r - l);
      return;
    }
    select_min(a, b, x, k * 2 + 1, l, (l + r) >> 1);
    select_min(a, b, x, k * 2 + 2, (l + r) >> 1, r);
    update(k);
  }
  void select_max(size_type a, size_type b, const X & x, size_type k, size_type l, size_type r) {
    eval(k, r - l);
    if(b <= l || r <= a || !(min0[k] < x)) return;
    // dump("select_max", k, l, r, r - l, min0[k], min1[k], cnt_min0[k]);
    if(a <= l && r <= b && x < min1[k]) {
      L[k] = x;
      eval(k, r - l);
      // dump("select_max R", k, l, r, r - l, min0[k], min1[k], max0[k], max1[k], cnt_min0[k]);
      return;
    }
    select_max(a, b, x, k * 2 + 1, l, (l + r) >> 1);
    select_max(a, b, x, k * 2 + 2, (l + r) >> 1, r);
    update(k);
    // dump("select_max Q", k, l, r, r - l, min0[k], min1[k], max0[k], max1[k], cnt_min0[k]);
  }
public:
  void range_add(index_type l, index_type r, const X &v) {
    if(l < 0) l = 0;
    if(r > static_cast<index_type>(_size)) r = _size;
    if(l >= r) return;
    range_add(l, r, v, 0, 0, n);
  }
private:
  void range_add(size_type a, size_type b, const X &v, size_type k, size_type l, size_type r) {
    eval(k, r - l);
    // dump("add", l, r, data[k], min0[k], min1[k], max0[k], max1[k], cnt_min0[k]);
    if(b <= l || r <= a) return;
    if(a <= l && r <= b) {
      add[k] = v;
      eval(k, r - l);
      // dump("add R", l, r, data[k], min0[k], min1[k], max0[k], max1[k], cnt_min0[k]);
      return;
    }
    range_add(a, b, v, k * 2 + 1, l, (l + r) >> 1);
    range_add(a, b, v, k * 2 + 2, (l + r) >> 1, r);
    update(k);
    // dump("add Q", l, r, data[k], min0[k], min1[k], max0[k], max1[k], cnt_min0[k]);
  }
public:
  const X addition_identity = 0; // TODO
  underlying_set range_sum(index_type l, index_type r) {
    // dump("start");
    if(l < 0) l = 0;
    if(r > static_cast<index_type>(_size)) r = _size;
    if(l >= r) return X(0);
    return range_sum(l, r, 0, 0, n);
  }
private:
  underlying_set range_sum(size_type a, size_type b, size_type k, size_type l, size_type r) {
    if(b <= l || r <= a) return identity;
    // dump("sum", l, r, data[k], min0[k], min1[k], max0[k], max1[k]);
    eval(k, r - l);
    // dump("sum", l, r, data[k], min0[k], min1[k], max0[k], max1[k]);
    if(a <= l && r <= b) return data[k];
    return range_sum(a, b, k * 2 + 1, l, (l + r) >> 1) + range_sum(a, b, k * 2 + 2, (l + r) >> 1, r);
  }
public:
  size_type size() {
    return _size;
  }
};

/// }}}--- ///

using namespace std;
#include "gtest/gtest.h"

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
  void range_add(int l, int r, T x) {
    for(int i = l; i < r; i++) data.at(i) += x;
  }
  T range_sum(int l, int r) {
    T s(0);
    for(int i = l; i < r; i++) s += data.at(i);
    return s;
  }
  void set_positive_infinity(int l, int r) {
    for(int i = l; i < r; i++) data.at(i) = T::positive_infinity;
  }
  void set_negative_infinity(int l, int r) {
    for(int i = l; i < r; i++) data.at(i) = T::negative_infinity;
  }
};

TEST(BeatsTest, Simple) {
  SegmentTreeBeats<add_inf<int>> a({7, 45, 2, 34, 23, 49 ,12 ,5});

  EXPECT_EQ(a.size(), 8);
  
  EXPECT_EQ(a.range_sum(2, 4), 36);
  EXPECT_EQ(a.range_sum(1, 5), 45 + 2 + 34 + 23);
  EXPECT_EQ(a.range_sum(0, 1), 7);
  EXPECT_EQ(a.range_sum(4, 4), 0);
  EXPECT_EQ(a.get(6), 12);
  
  a.select_min(1, 4, 10);
  // {7, 10, 2, 10, 23, 49 ,12 ,5}
  EXPECT_EQ(a.range_sum(2, 4), 12);
  EXPECT_EQ(a.range_sum(1, 5), 10 + 2 + 10 + 23);
  EXPECT_EQ(a.range_sum(0, 1), 7);
  EXPECT_EQ(a.range_sum(4, 4), 0);
  EXPECT_EQ(a.get(2), 2);
  EXPECT_EQ(a.get(3), 10);
  EXPECT_EQ(a.get(4), 23);
  
  a.select_max(3, 7, 13);
  a.set(0, 3);
  // {3, 10, 2, 13, 23, 49 ,13 ,5}
  EXPECT_EQ(a.range_sum(2, 4), 2 + 13);
  EXPECT_EQ(a.range_sum(1, 5), 10 + 2 + 13 + 23);
  EXPECT_EQ(a.range_sum(0, 1), 3);
  EXPECT_EQ(a.range_sum(4, 4), 0);
  EXPECT_EQ(a.get(6), 13);
  EXPECT_EQ(a.get(7), 5);

  a.set(3, 5);
  a.range_add(0, 7, -4);
  // {-1, 6, -2, 1, 19, 45 ,9 ,5}
  EXPECT_EQ(a.range_sum(2, 4), -1);
  EXPECT_EQ(a.range_sum(1, 5), 6 - 2 + 1 + 19);
  EXPECT_EQ(a.range_sum(0, 1), -1);
  EXPECT_EQ(a.range_sum(4, 4), 0);
  EXPECT_EQ(a.get(6), 9);
  EXPECT_EQ(a.get(7), 5);

}

class BeatsSuite : public ::testing::TestWithParam<std::tuple<int, int, int, std::vector<int>>> {};

TEST_P(BeatsSuite, RandomMedium) {

  int n, q, r;
  vector<int> distribution;

  tie(n, q, r, distribution) = GetParam();


  Naive<add_inf<int>> naive(n);
  using Seg = SegmentTreeBeats<add_inf<int>>;
  Seg beats(n);

  std::cout << "n : " << n << std::endl;


  mt19937 mt(1333);
  vector<int> ops;


  for(int i = 0; i < 6; i++) for(int j = 0; j < distribution[i]; j++) ops.push_back(i);

  uniform_int_distribution<int> rdop(0, ops.size() - 1);
  uniform_int_distribution<int> rdidx(0, n - 1);
  uniform_int_distribution<int> rdnum(-r, r);
  uniform_int_distribution<int> rd_sel_inf(0, 1);

  map<int, int> counts;

  for(int i = 0; i < q; i++) {
    int l = rdidx(mt), r = rdidx(mt);
    if(l > r) swap(l, r);
    r++;
    int num = rdnum(mt);
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
        // 2 : range_add
        naive.range_add(l, r, num);
        beats.range_add(l, r, num);
        break;
      case 3:
        // 3 : range_sum
        ASSERT_EQ(naive.range_sum(l, r), beats.range_sum(l, r)) << "\n"
          << "  n : " << n
          << "  q : " << q
          << "  q-id : " << i
          << "  range [" << l << ", " << r << ") "
          << "\n";
        break;
      case 4:
        // 4 : range_smin
        naive.select_min(l, r, num);
        beats.select_min(l, r, num);
        break;
      case 5:
        // 5 : range_smax
        naive.select_max(l, r, num);
        beats.select_max(l, r, num);
        break;
      case 6:
        // 6 : set_negative_infinity
        naive.set_negative_infinity(l, r);
        beats.set_negative_infinity(l, r);
        break;
      case 7:
        // 7 : set_positive_infinity
        naive.set_positive_infinity(l, r);
        beats.set_positive_infinity(l, r);
        break;
      default: FAIL() << "error";
    }
  }
  ASSERT_EQ(beats.size(), n);
}

// 0 : set
// 1 : get
// 2 : range_add
// 3 : range_sum
// 4 : range_smin
// 5 : range_smax

INSTANTIATE_TEST_CASE_P(one, BeatsSuite, ::testing::Combine(
    ::testing::Values(1, 40, 1000),
    ::testing::Values(2000),
    ::testing::Values(1000),
    ::testing::Values(
      vector<int>({2, 2, 3, 3, 1, 1, 1, 1}),
      vector<int>({100, 100, 70, 70, 3, 3, 1, 1})
      )
    )
  );

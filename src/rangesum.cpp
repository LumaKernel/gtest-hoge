
// total of range(l, r, step)
// rangesum(l, r [, step]) {{{
#include <cassert>
#include <utility>
long long rangesum(long long l, long long r) {
  return (r + l) * (r - l + 1) / 2;
}

long long rangesum(long long l, long long r, long long step) {
  if(l == r) return l;
  // struct DO_NOT_ZEROSTEP_WITH_NONZERO_RANGE{} ex;
  assert(step != 0);
  
  if(step > 0) {
    if(l > r) return l;

    auto n = (r - l + 1 + step - 1) / step;
    return n * l + n * (n - 1) / 2 * step;
  } else {
    if(l < r) return l;

    auto n = (l - r + 1 + -step - 1) / -step;
    return n * l + n * (n - 1) / 2 * step;
  }
}
// }}}


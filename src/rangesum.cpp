
// total of range(l, r, step)
// rangesum(l, r [, step]) {{{
#include <cassert>
#include <utility>
long long rangesum(long long l, long long r) {
  return (r + l) * (r - l + 1) / 2;
}

long long rangesum(long long l, long long r, long long step) {
  if(l == r) return l;
  assert(step != 0);
  
  if(step < 0) step = -step, std::swap(l, r);

  if(l > r) return l;
  
  auto n = (r - l + 1 + step - 1) / step;
  return n * l + n * (n - 1) / 2 * step;
}
// }}}


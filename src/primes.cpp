// O(N log log N)
/// --- primes {{{ ///
#include <vector>
std::vector< int > primes(int n) {
  std::vector< int > res;
  for(int i = 2; i <= n; ++i) {
    bool isp = 1;
    for(int p : res) {
      // if(static_cast<long long>(p) * p > i) break;
      if(static_cast<long long>(p * p) > i) break;
      if(i % p == 0) {
        isp = 0;
        break;
      }
    }
    if(isp) res.emplace_back(i);
  }
  return res;
}
/// }}}--- ///


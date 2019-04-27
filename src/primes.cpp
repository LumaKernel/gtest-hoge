// O(N log log N)
/// --- primes {{{ ///
#include <vector>
std::vector< int > primes(int n) {
  std::vector< int > res;
  for(int i = 2; i <= n; ++i) {
    bool is_prime = 1;
    for(int p : res) {
      if(static_cast<long long>(p) * p > i) break;
      if(i % p == 0) {
        is_prime = 0;
        break;
      }
    }
    if(is_prime) res.emplace_back(i);
  }
  return res;
}
/// }}}--- ///


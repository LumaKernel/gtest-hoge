// O(N^.5)
/// --- isPrime {{{ ///
bool isPrime(long long n) {
  if(n < 2) return false;
  for(long long i = 2; i * i <= n; i++) {
    if(n % i == 0) return false;
  }
  return true;
}
/// }}}--- ///


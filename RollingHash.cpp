#include<bits/stdc++.h>

// RollingHash(base): 基数base mod 2^61-1のローリングハッシュを構築
// generate_base(): 2^61-1以下の乱数生成
// build(s): 文字列sのハッシュテーブルを返す O(|s|)
// query(s,l,r): sの区間[l,r)のハッシュ値を返す
// combine(h1,h2,h2len):ハッシュ値h1と長さh2lenのハッシュ値h2を結合
// lcp(a,l1,r1,b,l2,r,): ハッシュテーブルaの区間[l1,r1)とハッシュテーブルbの区間[l2,r2)の文字列の最長共通接尾辞の長さを返す O(log(n))
struct RollingHash {
  static const uint64_t mod = (1ull << 61ull) - 1;
  using uint128_t = __uint128_t;
  std::vector< uint64_t > power;
  const uint64_t base;

  static inline uint64_t add(uint64_t a, uint64_t b) {
    if((a += b) >= mod) a -= mod;
    return a;
  }

  static inline uint64_t mul(uint64_t a, uint64_t b) {
    uint128_t c = (uint128_t) a * b;
    return add(c >> 61, c & mod);
  }

  static inline uint64_t generate_base() {
    std::mt19937_64 mt(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution< uint64_t > rand(1, RollingHash::mod - 1);
    return rand(mt);
  }

  inline void expand(size_t sz) {
    if(power.size() < sz + 1) {
      int pre_sz = (int) power.size();
      power.resize(sz + 1);
      for(int i = pre_sz - 1; i < sz; i++) {
        power[i + 1] = mul(power[i], base);
      }
    }
  }

  explicit RollingHash(uint64_t base = generate_base()) : base(base), power{1} {}

  std::vector< uint64_t > build(const std::string &s) const {
    int sz = s.size();
    std::vector< uint64_t > hashed(sz + 1);
    for(int i = 0; i < sz; i++) {
      hashed[i + 1] = add(mul(hashed[i], base), s[i]);
    }
    return hashed;
  }

  template< typename T >
  std::vector< uint64_t > build(const std::vector< T > &s) const {
    int sz = s.size();
    std::vector< uint64_t > hashed(sz + 1);
    for(int i = 0; i < sz; i++) {
      hashed[i + 1] = add(mul(hashed[i], base), s[i]);
    }
    return hashed;
  }

  uint64_t query(const std::vector< uint64_t > &s, int l, int r) {
    expand(r - l);
    return add(s[r], mod - mul(s[l], power[r - l]));
  }

  uint64_t combine(uint64_t h1, uint64_t h2, size_t h2len) {
    expand(h2len);
    return add(mul(h1, power[h2len]), h2);
  }

  int lcp(const std::vector< uint64_t > &a, int l1, int r1, const std::vector< uint64_t > &b, int l2, int r2) {
    int len = std::min(r1 - l1, r2 - l2);
    int low = 0, high = len + 1;
    while(high - low > 1) {
      int mid = (low + high) / 2;
      if(query(a, l1, l1 + mid) == query(b, l2, l2 + mid)) low = mid;
      else high = mid;
    }
    return low;
  }
};

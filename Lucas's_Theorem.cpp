#pragma once
#include<bits/stdc++.h>

template<class T> struct BiCoef_small_p{ // T: int or long long
    std::vector<T> fact_, inv_, finv_;
    int _mod;
    constexpr BiCoef_small_p(){};
    constexpr BiCoef_small_p(int p)noexcept : _mod(p), fact_(p, 1), inv_(p, 1), finv_(p, 1){
       init(p);
    }
    constexpr void init(int p) noexcept {
       fact_.assign(p, 1), inv_.assign(p, 1), finv_.assign(p, 1);
       _mod = p;
       for(int i = 2; i < _mod; i++){
            fact_[i] = fact_[i-1]*i % _mod;
            inv_[i] = _mod -inv_[_mod%i]*(_mod/i) % _mod;
            finv_[i] = finv_[i-1]*inv_[i] % _mod;
        }
    }
    constexpr T com(int n, int k) const noexcept {
        if(n < k || n < 0 || k < 0)return 0;
        T ans = 1;
        for(; n && k && ans; n/=_mod, k/=_mod){
            if(n%_mod >= k%_mod)ans *= fact_[n%_mod]*finv_[k%_mod]*finv_[n%_mod-k%_mod]%_mod;
            else ans = 0;
        }
        return ans;
    }
    constexpr T modpow(T x, T n){
        T ret = 1;
        while(n > 0){
            if(n & 1)ret *= x % _mod;
            x *= x % _mod;
            n >>= 1;
        }
        return ret;
    }
};
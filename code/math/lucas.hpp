#pragma once

#include "comb.hpp"
#include "euclid.hpp"

template<class Z>
Z lucas(ull n, ull k, const Comb<Z>& comb) {
    if (k > n) return 0;
    Z ans = 1;
    ull p = Z::mod();
    while (n || k) {
        int x = n % p, y = k % p;
        if (y > x) return 0;
        ans *= comb.C(x, y);
        n /= p;
        k /= p;
    }
    return ans;
}

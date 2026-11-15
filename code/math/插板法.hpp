#pragma once

#include "../types.hpp"
#include "comb.hpp"

template<class Z>
Z boundedCompositions(int sum, int k, int cap, const Comb<Z>& comb) {
    if (!k) return sum == 0;
    Z ans = 0;
    ll step = 1LL + cap;
    for (int j = 0; j <= k && j <= sum / step; ++j) {
        int left = static_cast<int>(sum - j * step);
        Z term = comb.C(k, j) * comb.C(left + (k - 1), k - 1);
        if (j & 1) ans -= term;
        else ans += term;
    }
    return ans;
}

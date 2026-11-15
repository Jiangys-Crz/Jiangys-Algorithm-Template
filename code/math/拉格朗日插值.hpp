#pragma once

#include "comb.hpp"

template<class Z>
Z lagrangeConsecutive(const std::vector<Z>& y, Z x, const Comb<Z>& comb) {
    int n = static_cast<int>(y.size()) - 1;
    if (x.val() < y.size()) return y[x.val()];

    std::vector<Z> pre(n + 2, 1), suf(n + 2, 1);
    for (int i = 0; i <= n; ++i) pre[i + 1] = pre[i] * (x - i);
    for (int i = n; i >= 0; --i) suf[i] = suf[i + 1] * (x - i);

    Z res = 0;
    for (int i = 0; i <= n; ++i) {
        Z term = y[i] * pre[i] * suf[i + 1] *
                 comb.invfac(i) * comb.invfac(n - i);
        if ((n - i) & 1) res -= term;
        else res += term;
    }
    return res;
}

#pragma once

#include "comb.hpp"

template<class Z>
Z derangement(int n) {
    if (!n) return 1;
    Z a = 1, b = 0;
    for (int i = 2; i <= n; ++i) {
        Z c = Z(i - 1) * (a + b);
        a = b;
        b = c;
    }
    return b;
}

template<class Z>
Z catalan(int n, const Comb<Z>& comb) {
    return comb.C(2 * n, n) - comb.C(2 * n, n - 1);
}

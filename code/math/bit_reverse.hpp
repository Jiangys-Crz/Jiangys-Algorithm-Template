#include <cassert>
#include <utility>
#include <vector>

#ifndef XCPC_MATH_BIT_REVERSE_HPP
#define XCPC_MATH_BIT_REVERSE_HPP

template<class T>
void bitReverse(vector<T>& a) {
    auto n = a.size();
    assert(n && !(n & (n - 1)));
    for (size_t i = 1, j = 0; i < n; ++i) {
        size_t bit = n / 2;
        while (j & bit) {
            j ^= bit;
            bit >>= 1;
        }
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
}

#endif

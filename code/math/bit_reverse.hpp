#pragma once

#include <cassert>
#include <utility>
#include <vector>

template<class T>
void bitReverse(std::vector<T>& a) {
    auto n = a.size();
    assert(n && !(n & (n - 1)));
    for (std::size_t i = 1, j = 0; i < n; ++i) {
        std::size_t bit = n / 2;
        while (j & bit) {
            j ^= bit;
            bit >>= 1;
        }
        j ^= bit;
        if (i < j) std::swap(a[i], a[j]);
    }
}

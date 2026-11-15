#include <vector>

#include "../types.hpp"

std::vector<ll> suffixSums(const std::vector<int>& a) {
    int n = static_cast<int>(a.size());
    std::vector<ll> suf(n + 2, 0);
    for (int i = n; i >= 1; --i) {
        suf[i] = a[i - 1] + suf[i + 1];
    }
    return suf;
}

ll suffixRangeSum(const std::vector<ll>& suf, int l, int r) {
    return suf[l] - suf[r + 1];
}

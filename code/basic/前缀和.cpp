#include <vector>

#include "../types.hpp"

std::vector<ll> prefixSums(const std::vector<int>& a) {
    int n = static_cast<int>(a.size());
    std::vector<ll> pre(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        pre[i] = pre[i - 1] + a[i - 1];
    }
    return pre;
}

ll prefixRangeSum(const std::vector<ll>& pre, int l, int r) {
    return pre[r] - pre[l - 1];
}

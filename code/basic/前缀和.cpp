#include <vector>

std::vector<long long> prefixSums(const std::vector<int>& a) {
    int n = static_cast<int>(a.size());
    std::vector<long long> pre(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        pre[i] = pre[i - 1] + a[i - 1];
    }
    return pre;
}

long long prefixRangeSum(const std::vector<long long>& pre, int l, int r) {
    return pre[r] - pre[l - 1];
}

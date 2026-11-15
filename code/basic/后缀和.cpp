#include <vector>

std::vector<long long> suffixSums(const std::vector<int>& a) {
    int n = static_cast<int>(a.size());
    std::vector<long long> suf(n + 2, 0);
    for (int i = n; i >= 1; --i) {
        suf[i] = a[i - 1] + suf[i + 1];
    }
    return suf;
}

long long suffixRangeSum(const std::vector<long long>& suf, int l, int r) {
    return suf[l] - suf[r + 1];
}

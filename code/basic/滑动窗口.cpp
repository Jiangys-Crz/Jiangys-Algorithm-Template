#include <algorithm>
#include <vector>

int longestWindowAtMost(const std::vector<int>& a, long long limit) {
    int n = static_cast<int>(a.size());
    int l = 0, best = 0;
    long long sum = 0;
    for (int r = 0; r < n; ++r) {
        sum += a[r];
        while (l <= r && sum > limit) {
            sum -= a[l++];
        }
        best = std::max(best, r - l + 1);
    }
    return best;
}

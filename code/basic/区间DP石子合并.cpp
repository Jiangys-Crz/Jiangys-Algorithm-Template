#include <algorithm>
#include <vector>

long long minMergeCost(const std::vector<long long>& stones) {
    const int n = static_cast<int>(stones.size());
    if (n == 0) return 0;

    std::vector<long long> prefix(n + 1);
    for (int i = 0; i < n; ++i) {
        prefix[i + 1] = prefix[i] + stones[i];
    }

    std::vector<std::vector<long long>> dp(n, std::vector<long long>(n));
    for (int len = 2; len <= n; ++len) {
        for (int l = 0; l + len <= n; ++l) {
            const int r = l + len - 1;
            const long long cost = prefix[r + 1] - prefix[l];
            long long best = dp[l + 1][r];
            for (int k = l + 1; k < r; ++k) {
                best = std::min(best, dp[l][k] + dp[k + 1][r]);
            }
            dp[l][r] = best + cost;
        }
    }
    return dp[0][n - 1];
}

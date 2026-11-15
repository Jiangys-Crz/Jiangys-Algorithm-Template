#include <algorithm>
#include <vector>

#include "../types.hpp"

ll minMergeCost(const std::vector<ll>& stones) {
    const int n = static_cast<int>(stones.size());
    if (n == 0) return 0;

    std::vector<ll> prefix(n + 1);
    for (int i = 0; i < n; ++i) {
        prefix[i + 1] = prefix[i] + stones[i];
    }

    std::vector<std::vector<ll>> dp(n, std::vector<ll>(n));
    for (int len = 2; len <= n; ++len) {
        for (int l = 0; l + len <= n; ++l) {
            const int r = l + len - 1;
            const ll cost = prefix[r + 1] - prefix[l];
            ll best = dp[l + 1][r];
            for (int k = l + 1; k < r; ++k) {
                best = std::min(best, dp[l][k] + dp[k + 1][r]);
            }
            dp[l][r] = best + cost;
        }
    }
    return dp[0][n - 1];
}

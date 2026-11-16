#include <algorithm>
#include <limits>
#include <vector>

using ll = long long;

// In solve: int n; every [l, r] has at least one valid split if l < r.
// TODO: Prepare any data needed to compute the split cost.
std::vector<std::vector<ll>> dp(n, std::vector<ll>(n));
for (int len = 2; len <= n; ++len) {
    for (int l = 0; l <= n - len; ++l) {
        int r = l + len - 1;
        ll best = std::numeric_limits<ll>::max();
        for (int k = l; k < r; ++k) {
            // Cost of merging [l, k] and [k + 1, r].
            ll cost = /* TODO: merge cost for this split */;
            best = std::min(best, dp[l][k] + dp[k + 1][r] + cost);
        }
        dp[l][r] = best;
    }
}
ll ans = n == 0 ? 0 : dp[0][n - 1];

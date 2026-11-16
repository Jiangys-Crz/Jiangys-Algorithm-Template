#include <algorithm>
#include <limits>
#include <vector>

using ll = long long;

// 序列长度为 n。每个长度至少为 2 的区间 [l, r] 至少有一种合法划分。
// 待填写：预处理计算合并代价所需的数据。
vector<vector<ll>> dp(n, vector<ll>(n));
for (int len = 2; len <= n; ++len) {
    for (int l = 0; l <= n - len; ++l) {
        int r = l + len - 1;
        ll best = numeric_limits<ll>::max();
        for (int k = l; k < r; ++k) {
            // 计算合并 [l, k] 和 [k + 1, r] 的代价。
            ll cost = /* 待填写：本次划分的合并代价 */;
            best = min(best, dp[l][k] + dp[k + 1][r] + cost);
        }
        dp[l][r] = best;
    }
}
ll ans = n == 0 ? 0 : dp[0][n - 1];

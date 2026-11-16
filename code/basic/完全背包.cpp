#include <algorithm>
#include <vector>

using ll = long long;

// V 为容量，items 保存各物品的重量和价值。
// 重量均为正整数。dp[V] 为总重量不超过 V 时的最大价值。

vector<ll> dp(V + 1);
for (auto [w, v] : items) {
    for (int c = w; c <= V; ++c) {
        dp[c] = max(dp[c], dp[c - w] + v);
    }
}

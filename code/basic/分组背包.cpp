#include <algorithm>
#include <vector>

using ll = long long;

// capacity 为容量，groups 按组保存物品的重量和价值。
// 重量均为正整数，每组最多选择一件物品。

vector<ll> dp(capacity + 1);
for (const auto& group : groups) {
    if (group.empty()) continue;
    auto next = dp;
    for (auto [weight, value] : group) {
        for (int c = weight; c <= capacity; ++c) {
            next[c] = max(next[c], dp[c - weight] + value);
        }
    }
    dp.swap(next);
}

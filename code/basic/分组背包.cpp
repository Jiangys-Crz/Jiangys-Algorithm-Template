#include <algorithm>
#include <vector>

using ll = long long;

// In solve: int capacity; groups is a list of groups of (weight, value).
// Weights are positive. Each group may contribute at most one item.

std::vector<ll> dp(capacity + 1);
for (const auto& group : groups) {
    if (group.empty()) continue;
    auto next = dp;
    for (auto [weight, value] : group) {
        for (int c = weight; c <= capacity; ++c) {
            next[c] = std::max(next[c], dp[c - weight] + value);
        }
    }
    dp.swap(next);
}

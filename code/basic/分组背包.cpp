#include <algorithm>
#include <utility>
#include <vector>

using ll = long long;

ll groupedKnapsack(
    int capacity,
    const std::vector<std::vector<std::pair<int, ll>>>& groups) {
    std::vector<ll> dp(capacity + 1);
    for (const auto& group : groups) {
        if (group.empty()) continue;
        auto next = dp;
        for (const auto& [weight, value] : group) {
            for (int c = weight; c <= capacity; ++c) {
                next[c] = std::max(next[c], dp[c - weight] + value);
            }
        }
        dp.swap(next);
    }
    return dp.back();
}

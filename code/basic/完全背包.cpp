#include <algorithm>
#include <utility>
#include <vector>

using ll = long long;

ll completeKnapsack(int capacity,
                           const std::vector<std::pair<int, ll>>& items) {
    std::vector<ll> dp(capacity + 1);
    for (const auto& [weight, value] : items) {
        for (int c = weight; c <= capacity; ++c) {
            dp[c] = std::max(dp[c], dp[c - weight] + value);
        }
    }
    return dp.back();
}

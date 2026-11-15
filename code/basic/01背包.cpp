#include <algorithm>
#include <utility>
#include <vector>

using ll = long long;

ll knapsack01(int capacity,
                     const std::vector<std::pair<int, ll>>& items) {
    std::vector<ll> dp(capacity + 1);
    for (const auto& [weight, value] : items) {
        for (int c = capacity; c >= weight; --c) {
            dp[c] = std::max(dp[c], dp[c - weight] + value);
        }
    }
    return dp.back();
}

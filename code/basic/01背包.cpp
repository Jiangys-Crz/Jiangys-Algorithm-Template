#include <algorithm>
#include <utility>
#include <vector>

long long knapsack01(int capacity,
                     const std::vector<std::pair<int, long long>>& items) {
    std::vector<long long> dp(capacity + 1);
    for (const auto& [weight, value] : items) {
        for (int c = capacity; c >= weight; --c) {
            dp[c] = std::max(dp[c], dp[c - weight] + value);
        }
    }
    return dp.back();
}

#include <algorithm>
#include <vector>

#include "../types.hpp"

struct BoundedItem {
    int weight;
    ll value;
    int count;
};

ll boundedKnapsack(int capacity, const std::vector<BoundedItem>& items) {
    std::vector<ll> dp(capacity + 1);
    for (const auto& [weight, value, count] : items) {
        int remaining = std::min(count, capacity / weight);
        for (ll batch = 1; remaining > 0; batch *= 2) {
            int copies = static_cast<int>(std::min<ll>(batch, remaining));
            remaining -= copies;
            int batchWeight = copies * weight;
            ll batchValue = copies * value;
            for (int c = capacity; c >= batchWeight; --c) {
                dp[c] = std::max(dp[c], dp[c - batchWeight] + batchValue);
            }
        }
    }
    return dp.back();
}

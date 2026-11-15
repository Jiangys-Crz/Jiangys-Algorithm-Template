#include <algorithm>
#include <vector>

struct BoundedItem {
    int weight;
    long long value;
    int count;
};

long long boundedKnapsack(int capacity, const std::vector<BoundedItem>& items) {
    std::vector<long long> dp(capacity + 1);
    for (const auto& [weight, value, count] : items) {
        int remaining = std::min(count, capacity / weight);
        for (long long batch = 1; remaining > 0; batch *= 2) {
            int copies = static_cast<int>(std::min<long long>(batch, remaining));
            remaining -= copies;
            int batchWeight = copies * weight;
            long long batchValue = copies * value;
            for (int c = capacity; c >= batchWeight; --c) {
                dp[c] = std::max(dp[c], dp[c - batchWeight] + batchValue);
            }
        }
    }
    return dp.back();
}

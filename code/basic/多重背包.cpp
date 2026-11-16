#include <algorithm>
#include <vector>

using ll = long long;

// In solve: int capacity; items contains (weight, value, count).
// Every weight is positive and every count is nonnegative.

std::vector<ll> dp(capacity + 1);
for (auto [weight, value, count] : items) {
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

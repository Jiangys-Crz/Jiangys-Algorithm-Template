#include <algorithm>
#include <vector>

using ll = long long;

// capacity 为容量，items 保存各物品的重量、价值和数量。
// 重量均为正整数，数量均为非负整数。

vector<ll> dp(capacity + 1);
for (auto [weight, value, count] : items) {
    int remaining = min(count, capacity / weight);
    for (ll batch = 1; remaining > 0; batch *= 2) {
        int copies = static_cast<int>(min<ll>(batch, remaining));
        remaining -= copies;
        int batchWeight = copies * weight;
        ll batchValue = copies * value;
        for (int c = capacity; c >= batchWeight; --c) {
            dp[c] = max(dp[c], dp[c - batchWeight] + batchValue);
        }
    }
}

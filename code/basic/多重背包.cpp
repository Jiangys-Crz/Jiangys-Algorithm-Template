#include <iostream>
#include <algorithm>
#include <vector>

using ll = long long;

int main() {
    int n, capacity;
    if (!(std::cin >> n >> capacity)) return 0;
    std::vector<ll> dp(capacity + 1);
    for (int i = 0; i < n; ++i) {
        int weight, count;
        ll value;
        std::cin >> weight >> value >> count;
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
    std::cout << dp[capacity] << '\n';
}

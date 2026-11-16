#include <algorithm>
#include <vector>

using ll = long long;

// In solve: int V is the capacity; items contains pairs (weight, value).
// All weights are positive. dp[V] is the maximum value within capacity V.

std::vector<ll> dp(V + 1);
for (auto [w, v] : items) {
    for (int c = V; c >= w; --c) {
        dp[c] = std::max(dp[c], dp[c - w] + v);
    }
}

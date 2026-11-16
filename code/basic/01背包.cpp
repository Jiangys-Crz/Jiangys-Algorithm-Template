#include <algorithm>
#include <iostream>
#include <vector>

using ll = long long;

int main() {
    int n, V;
    if (!(std::cin >> n >> V)) return 0;
    std::vector<ll> dp(V + 1);
    for (int i = 0; i < n; ++i) {
        int w;
        ll v;
        std::cin >> w >> v;
        for (int c = V; c >= w; --c) {
            dp[c] = std::max(dp[c], dp[c - w] + v);
        }
    }
    std::cout << dp[V] << '\n';
}

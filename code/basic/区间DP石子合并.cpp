#include <iostream>
#include <algorithm>
#include <vector>

using ll = long long;

int main() {
    int n;
    if (!(std::cin >> n)) return 0;
    if (n == 0) {
        std::cout << "0\n";
        return 0;
    }

    std::vector<ll> prefix(n + 1);
    for (int i = 0; i < n; ++i) {
        ll x;
        std::cin >> x;
        prefix[i + 1] = prefix[i] + x;
    }

    std::vector<std::vector<ll>> dp(n, std::vector<ll>(n));
    for (int len = 2; len <= n; ++len) {
        for (int l = 0; l + len <= n; ++l) {
            const int r = l + len - 1;
            const ll cost = prefix[r + 1] - prefix[l];
            ll best = dp[l + 1][r];
            for (int k = l + 1; k < r; ++k) {
                best = std::min(best, dp[l][k] + dp[k + 1][r]);
            }
            dp[l][r] = best + cost;
        }
    }
    std::cout << dp[0][n - 1] << '\n';
}

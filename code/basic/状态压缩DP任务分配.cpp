#include <iostream>
#include <algorithm>
#include <bitset>
#include <limits>
#include <vector>

using ll = long long;

int main() {
    int n;
    if (!(std::cin >> n)) return 0;
    std::vector<std::vector<ll>> cost(n, std::vector<ll>(n));
    for (auto& row : cost) {
        for (ll& x : row) std::cin >> x;
    }

    const unsigned states = 1u << n;
    std::vector<ll> dp(states, std::numeric_limits<ll>::max());
    dp[0] = 0;

    for (unsigned mask = 0; mask + 1 < states; ++mask) {
        const auto worker = std::bitset<20>(mask).count();
        for (int task = 0; task < n; ++task) {
            const unsigned bit = 1u << task;
            if (mask & bit) continue;
            const unsigned next = mask | bit;
            dp[next] = std::min(dp[next], dp[mask] + cost[worker][task]);
        }
    }
    std::cout << dp.back() << '\n';
}

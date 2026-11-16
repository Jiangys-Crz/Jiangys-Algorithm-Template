#include <algorithm>
#include <bitset>
#include <limits>
#include <vector>

using ll = long long;

// In solve: int n (0..20); cost[i][j] assigns task j to person i.

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
ll ans = dp.back();

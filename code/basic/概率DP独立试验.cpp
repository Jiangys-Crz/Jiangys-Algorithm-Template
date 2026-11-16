#include <cstddef>
#include <vector>

// In solve: probabilities for independent trials, and int k with 0 <= k <= n.

std::vector<long double> dp(static_cast<std::size_t>(k) + 1);
dp[0] = 1;

int maxSuccesses = 0;
for (long double p : probabilities) {
    if (maxSuccesses < k) ++maxSuccesses;
    for (int successes = maxSuccesses; successes > 0; --successes) {
        dp[successes] = (1 - p) * dp[successes] + p * dp[successes - 1];
    }
    dp[0] *= 1 - p;
}
long double ans = dp[k];

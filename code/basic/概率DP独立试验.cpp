#include <cstddef>
#include <vector>

long double probabilityOfExactlyK(const std::vector<long double>& probabilities,
                                  int k) {
    if (k < 0 || static_cast<std::size_t>(k) > probabilities.size()) return 0;
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
    return dp[k];
}

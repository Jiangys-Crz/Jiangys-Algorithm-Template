#include <iomanip>
#include <iostream>
#include <cstddef>
#include <vector>

int main() {
    int n, k;
    if (!(std::cin >> n >> k)) return 0;
    if (k < 0 || k > n) {
        std::cout << "0\n";
        return 0;
    }
    std::vector<long double> dp(static_cast<std::size_t>(k) + 1);
    dp[0] = 1;

    int maxSuccesses = 0;
    for (int i = 0; i < n; ++i) {
        long double p;
        std::cin >> p;
        if (maxSuccesses < k) ++maxSuccesses;
        for (int successes = maxSuccesses; successes > 0; --successes) {
            dp[successes] = (1 - p) * dp[successes] + p * dp[successes - 1];
        }
        dp[0] *= 1 - p;
    }
    std::cout << std::setprecision(15) << dp[k] << '\n';
}

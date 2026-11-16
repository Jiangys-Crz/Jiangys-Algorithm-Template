#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>

// In solve: strings a and b. Use the shorter string for columns.

if (a.size() < b.size()) a.swap(b);
std::vector<std::size_t> dp(b.size() + 1);
for (char x : a) {
    std::size_t diagonal = 0;
    for (std::size_t j = 1; j <= b.size(); ++j) {
        std::size_t above = dp[j];
        if (x == b[j - 1]) dp[j] = diagonal + 1;
        else dp[j] = std::max(dp[j], dp[j - 1]);
        diagonal = above;
    }
}
std::size_t ans = dp.back();

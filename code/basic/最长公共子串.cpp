#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>

// In solve: strings a and b. Use the shorter string for columns.

if (a.size() < b.size()) a.swap(b);
std::vector<std::size_t> dp(b.size() + 1);
std::size_t best = 0;
for (char x : a) {
    for (std::size_t j = b.size(); j > 0; --j) {
        dp[j] = x == b[j - 1] ? dp[j - 1] + 1 : 0;
        best = std::max(best, dp[j]);
    }
}
std::size_t ans = best;

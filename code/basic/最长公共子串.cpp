#include <algorithm>
#include <cstddef>
#include <string_view>
#include <vector>

std::size_t longestCommonSubstring(std::string_view a, std::string_view b) {
    if (a.size() < b.size()) a.swap(b);
    if (b.empty()) return 0;
    std::vector<std::size_t> dp(b.size() + 1);
    std::size_t best = 0;
    for (char x : a) {
        for (std::size_t j = b.size(); j > 0; --j) {
            dp[j] = x == b[j - 1] ? dp[j - 1] + 1 : 0;
            best = std::max(best, dp[j]);
        }
    }
    return best;
}

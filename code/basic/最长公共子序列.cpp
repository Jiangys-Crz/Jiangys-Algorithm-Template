#include <algorithm>
#include <cstddef>
#include <string_view>
#include <vector>

std::size_t lcsLength(std::string_view a, std::string_view b) {
    if (a.size() < b.size()) a.swap(b);
    if (b.empty()) return 0;
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
    return dp.back();
}

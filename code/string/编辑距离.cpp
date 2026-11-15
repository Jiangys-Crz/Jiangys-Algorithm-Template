#include <algorithm>
#include <numeric>
#include <string_view>
#include <vector>

int editDistance(std::string_view a, std::string_view b) {
    if (a.size() < b.size()) a.swap(b);
    std::vector<int> dp(b.size() + 1);
    std::iota(dp.begin(), dp.end(), 0);

    for (char x : a) {
        int diag = dp[0]++;
        for (std::size_t j = 1; j <= b.size(); ++j) {
            int up = dp[j];
            dp[j] = std::min({up + 1, dp[j - 1] + 1,
                              diag + (x != b[j - 1])});
            diag = up;
        }
    }
    return dp.back();
}

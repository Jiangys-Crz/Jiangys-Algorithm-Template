#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>

// 先准备字符串 a 和 b，以较短的串为列。

if (a.size() < b.size()) a.swap(b);
vector<size_t> dp(b.size() + 1);
for (char x : a) {
    size_t diagonal = 0;
    for (size_t j = 1; j <= b.size(); ++j) {
        size_t above = dp[j];
        if (x == b[j - 1]) dp[j] = diagonal + 1;
        else dp[j] = max(dp[j], dp[j - 1]);
        diagonal = above;
    }
}
size_t ans = dp.back();

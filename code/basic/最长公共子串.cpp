#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>

// 先准备字符串 a 和 b，以较短的串为列。

if (a.size() < b.size()) a.swap(b);
vector<size_t> dp(b.size() + 1);
size_t best = 0;
for (char x : a) {
    for (size_t j = b.size(); j > 0; --j) {
        dp[j] = x == b[j - 1] ? dp[j - 1] + 1 : 0;
        best = max(best, dp[j]);
    }
}
size_t ans = best;

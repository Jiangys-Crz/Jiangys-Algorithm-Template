#include <algorithm>
#include <string>
#include <vector>

// 先准备字符串 s。ans 为最长回文子序列的长度。

int n = static_cast<int>(s.size());
vector<int> dp(n);
for (int i = n - 1; i >= 0; --i) {
    dp[i] = 1;
    int diag = 0;
    for (int j = i + 1; j < n; ++j) {
        int old = dp[j];
        if (s[i] == s[j]) dp[j] = diag + 2;
        else dp[j] = max(dp[j], dp[j - 1]);
        diag = old;
    }
}
int ans = n == 0 ? 0 : dp.back();

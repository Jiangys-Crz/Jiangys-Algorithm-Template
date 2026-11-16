#include <algorithm>
#include <string>
#include <vector>

// In solve: string or string_view s. ans is the longest palindromic subsequence length.

int n = static_cast<int>(s.size());
std::vector<int> dp(n);
for (int i = n - 1; i >= 0; --i) {
    dp[i] = 1;
    int diag = 0;
    for (int j = i + 1; j < n; ++j) {
        int old = dp[j];
        if (s[i] == s[j]) dp[j] = diag + 2;
        else dp[j] = std::max(dp[j], dp[j - 1]);
        diag = old;
    }
}
int ans = n == 0 ? 0 : dp.back();

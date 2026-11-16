#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

int main() {
    std::string s;
    if (!std::getline(std::cin, s)) return 0;
    int n = static_cast<int>(s.size());
    if (!n) {
        std::cout << "0\n";
        return 0;
    }

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
    std::cout << dp.back() << '\n';
}

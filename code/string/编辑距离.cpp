#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::string a, b;
    if (!std::getline(std::cin, a) || !std::getline(std::cin, b)) return 0;
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
    std::cout << dp.back() << '\n';
}

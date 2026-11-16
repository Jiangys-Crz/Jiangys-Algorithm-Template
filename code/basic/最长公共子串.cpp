#include <iostream>
#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>

int main() {
    std::string a, b;
    if (!std::getline(std::cin, a) || !std::getline(std::cin, b)) return 0;

    if (a.size() < b.size()) a.swap(b);
    if (b.empty()) {
        std::cout << "0\n";
        return 0;
    }
    std::vector<std::size_t> dp(b.size() + 1);
    std::size_t best = 0;
    for (char x : a) {
        for (std::size_t j = b.size(); j > 0; --j) {
            dp[j] = x == b[j - 1] ? dp[j - 1] + 1 : 0;
            best = std::max(best, dp[j]);
        }
    }
    std::cout << best << '\n';
}

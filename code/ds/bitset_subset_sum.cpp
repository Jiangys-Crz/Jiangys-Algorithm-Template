#include <bitset>
#include <iostream>

int main() {
    int n, target;
    if (!(std::cin >> n >> target)) return 0;
    constexpr int maxSum = 100000;
    std::bitset<maxSum + 1> dp;
    dp[0] = true;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        dp |= dp << x;
    }
    std::cout << dp[target] << '\n';
}

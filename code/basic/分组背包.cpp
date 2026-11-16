#include <iostream>
#include <algorithm>
#include <vector>

using ll = long long;

int main() {
    int groups, capacity;
    if (!(std::cin >> groups >> capacity)) return 0;
    std::vector<ll> dp(capacity + 1);
    for (int i = 0; i < groups; ++i) {
        int count;
        std::cin >> count;
        if (count == 0) continue;
        auto next = dp;
        for (int j = 0; j < count; ++j) {
            int weight;
            ll value;
            std::cin >> weight >> value;
            for (int c = weight; c <= capacity; ++c) {
                next[c] = std::max(next[c], dp[c - weight] + value);
            }
        }
        dp.swap(next);
    }
    std::cout << dp[capacity] << '\n';
}

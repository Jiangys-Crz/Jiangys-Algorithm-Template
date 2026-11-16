#include <algorithm>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

using ll = long long;

int main() {
    int n;
    if (!(std::cin >> n)) return 0;
    std::vector<std::pair<ll, ll>> a(n);
    for (auto& [l, r] : a) std::cin >> l >> r;
    std::sort(a.begin(), a.end(), [](const auto& x, const auto& y) {
        return x.second < y.second;
    });

    int ans = 0;
    ll last = std::numeric_limits<ll>::min();
    for (auto [l, r] : a) {
        if (l >= last) {
            ++ans;
            last = r;
        }
    }
    std::cout << ans << '\n';
}

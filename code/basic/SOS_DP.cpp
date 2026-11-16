#include <iostream>
#include <cstddef>
#include <vector>

using ll = long long;

int main() {
    int n;
    if (!(std::cin >> n)) return 0;
    std::vector<ll> values(std::size_t{1} << n);
    for (ll& x : values) std::cin >> x;

    for (int bit = 0; bit < n; ++bit) {
        const std::size_t flag = std::size_t{1} << bit;
        for (std::size_t mask = 0; mask < values.size(); ++mask) {
            if ((mask & flag) != 0) {
                values[mask] += values[mask ^ flag];
            }
        }
    }
    for (ll x : values) std::cout << x << ' ';
    std::cout << '\n';
}

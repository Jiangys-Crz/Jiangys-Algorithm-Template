#include <algorithm>
#include <iostream>
#include <vector>

using ll = long long;

int main() {
    int n, q;
    if (!(std::cin >> n >> q)) return 0;
    std::vector<ll> vals(n);
    for (ll& x : vals) std::cin >> x;
    std::sort(vals.begin(), vals.end());
    vals.erase(std::unique(vals.begin(), vals.end()), vals.end());

    while (q--) {
        ll x;
        std::cin >> x;
        auto it = std::lower_bound(vals.begin(), vals.end(), x);
        auto rank = it != vals.end() && *it == x ? it - vals.begin() + 1 : 0;
        std::cout << rank << '\n';
    }
}

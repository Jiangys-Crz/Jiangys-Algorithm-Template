#include <algorithm>
#include <iostream>
#include <vector>

using ll = long long;

int main() {
    int n;
    if (!(std::cin >> n)) return 0;
    std::vector<ll> tails;
    for (int i = 0; i < n; ++i) {
        ll x;
        std::cin >> x;
        auto it = std::lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    std::cout << tails.size() << '\n';
}

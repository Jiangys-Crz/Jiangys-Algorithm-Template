#include <algorithm>
#include <iostream>
#include <vector>

using ll = long long;

int main() {
    int n;
    ll x;
    if (!(std::cin >> n >> x)) return 0;
    std::vector<ll> a(n);
    for (ll& v : a) std::cin >> v;

    auto l = std::lower_bound(a.begin(), a.end(), x);
    auto r = std::upper_bound(l, a.end(), x);
    std::cout << l - a.begin() << ' ' << r - a.begin() << '\n';
}

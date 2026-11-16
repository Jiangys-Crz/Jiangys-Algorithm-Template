#include <iostream>
#include <iterator>
#include <set>

using ll = long long;

int main() {
    int n;
    ll x;
    if (!(std::cin >> n >> x)) return 0;
    std::multiset<ll> s;
    for (int i = 0; i < n; ++i) {
        ll v;
        std::cin >> v;
        s.insert(v);
    }

    auto it = s.find(x);
    if (it != s.end()) s.erase(it);

    auto l = s.lower_bound(x);
    auto r = s.upper_bound(x);
    if (l == s.begin()) std::cout << "NONE";
    else std::cout << *std::prev(l);
    std::cout << ' ';
    if (r == s.end()) std::cout << "NONE\n";
    else std::cout << *r << '\n';
}

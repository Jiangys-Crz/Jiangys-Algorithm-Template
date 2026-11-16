#include <iostream>
#include <vector>

using ll = long long;

int main() {
    int n, q;
    if (!(std::cin >> n >> q)) return 0;
    std::vector<ll> d(n + 2);
    ll prev = 0;
    for (int i = 1; i <= n; ++i) {
        ll x;
        std::cin >> x;
        d[i] = x - prev;
        prev = x;
    }

    while (q--) {
        int l, r;
        ll v;
        std::cin >> l >> r >> v;
        d[l] += v;
        d[r + 1] -= v;
    }

    for (int i = 1; i <= n; ++i) {
        d[i] += d[i - 1];
        std::cout << d[i] << (i == n ? '\n' : ' ');
    }
}

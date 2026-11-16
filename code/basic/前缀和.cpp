#include <iostream>
#include <vector>

using ll = long long;

int main() {
    int n, q;
    if (!(std::cin >> n >> q)) return 0;
    std::vector<ll> pre(n + 1);
    for (int i = 1; i <= n; ++i) {
        ll x;
        std::cin >> x;
        pre[i] = pre[i - 1] + x;
    }

    while (q--) {
        int l, r;
        std::cin >> l >> r;
        std::cout << pre[r] - pre[l - 1] << '\n';
    }
}

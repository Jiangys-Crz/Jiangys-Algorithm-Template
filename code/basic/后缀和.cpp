#include <iostream>
#include <vector>

using ll = long long;

int main() {
    int n, q;
    if (!(std::cin >> n >> q)) return 0;
    std::vector<ll> a(n + 1), suf(n + 2);
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    for (int i = n; i >= 1; --i) suf[i] = a[i] + suf[i + 1];

    while (q--) {
        int l, r;
        std::cin >> l >> r;
        std::cout << suf[l] - suf[r + 1] << '\n';
    }
}

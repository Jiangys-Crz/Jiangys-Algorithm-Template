#include <iostream>
#include <vector>

using ll = long long;

int main() {
    int n;
    if (!(std::cin >> n)) return 0;

    std::vector<bool> st(n + 1);
    for (int p = 2; p <= n / p; ++p) {
        if (st[p]) continue;
        for (ll j = 1LL * p * p; j <= n; j += p) st[j] = true;
    }
    for (int i = 2; i <= n; ++i) {
        if (!st[i]) std::cout << i << ' ';
    }
    std::cout << '\n';
}

#include <algorithm>
#include <iostream>

using ll = long long;

int main() {
    int n;
    if (!(std::cin >> n)) return 0;
    ll twoBack = 0, oneBack = 0;
    for (int i = 0; i < n; ++i) {
        ll x;
        std::cin >> x;
        ll cur = std::max(oneBack, twoBack + x);
        twoBack = oneBack;
        oneBack = cur;
    }
    std::cout << oneBack << '\n';
}

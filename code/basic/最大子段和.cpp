#include <algorithm>
#include <iostream>

using ll = long long;

int main() {
    int n;
    ll ending;
    if (!(std::cin >> n >> ending)) return 0;
    ll ans = ending;
    for (int i = 1; i < n; ++i) {
        ll x;
        std::cin >> x;
        ending = x + std::max(0LL, ending);
        ans = std::max(ans, ending);
    }
    std::cout << ans << '\n';
}

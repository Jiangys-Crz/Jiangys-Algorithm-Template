#include <iostream>

using ull = unsigned long long;

int main() {
    ull a, b, m;
    if (!(std::cin >> a >> b >> m)) return 0;
    a %= m;
    b %= m;
    ull ans = 0;
    while (b) {
        if (b & 1) ans = ans >= m - a ? ans - (m - a) : ans + a;
        a = a >= m - a ? a - (m - a) : a + a;
        b >>= 1;
    }
    std::cout << ans << '\n';
}

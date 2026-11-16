#include <iostream>

using ull = unsigned long long;
using ulll = unsigned __int128;

int main() {
    ull a, b, m;
    if (!(std::cin >> a >> b >> m)) return 0;
    ull ans = 1 % m;
    a %= m;
    while (b) {
        if (b & 1) ans = ulll(ans) * a % m;
        a = ulll(a) * a % m;
        b >>= 1;
    }
    std::cout << ans << '\n';
}

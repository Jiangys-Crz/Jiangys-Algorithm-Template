#include <iostream>

using ull = unsigned long long;

int main() {
    ull n;
    if (!(std::cin >> n)) return 0;
    for (ull l = 1; l <= n; ) {
        ull q = n / l, r = n / q;
        std::cout << l << ' ' << r << ' ' << q << '\n';
        if (r == n) break;
        l = r + 1;
    }
}

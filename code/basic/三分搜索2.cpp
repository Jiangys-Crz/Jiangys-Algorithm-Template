#include <iomanip>
#include <iostream>

int main() {
    long double l, r, p;
    if (!(std::cin >> l >> r >> p)) return 0;
    auto f = [p](long double x) { return (x - p) * (x - p); };
    constexpr long double eps = 1e-8L;
    while (r - l > eps) {
        long double m1 = l + (r - l) / 3;
        long double m2 = r - (r - l) / 3;
        if (m1 == l || m2 == r || m1 >= m2) break;
        if (f(m1) > f(m2)) l = m1;
        else r = m2;
    }
    std::cout << std::fixed << std::setprecision(10) << l + (r - l) / 2 << '\n';
}

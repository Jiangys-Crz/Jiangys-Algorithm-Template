#include <algorithm>
#include <iomanip>
#include <iostream>

int main() {
    long double n;
    if (!(std::cin >> n)) return 0;
    long double l = 0, r = std::max(1.0L, n);
    constexpr long double eps = 1e-8L;
    while (r - l > eps) {
        long double mid = l + (r - l) / 2;
        if (mid == l || mid == r) break;
        if (mid * mid >= n) r = mid;
        else l = mid;
    }
    std::cout << std::fixed << std::setprecision(10) << r << '\n';
}

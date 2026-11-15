#include <vector>

long double atLeastOneIndependent(const std::vector<long double>& p) {
    long double ans = 0;
    for (long double x : p) ans += (1 - ans) * x;
    return ans;
}

long double expectedCouponDraws(int n) {
    long double ans = 0;
    for (int missing = n; missing >= 1; --missing) {
        ans += static_cast<long double>(n) / missing;
    }
    return ans;
}

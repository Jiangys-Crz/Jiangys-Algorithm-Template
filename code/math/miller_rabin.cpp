#include "mod_arithmetic.hpp"

bool isPrimeTrial(ull n) {
    if (n < 2) return false;
    if (!(n & 1)) return n == 2;
    for (ull p = 3; p <= n / p; p += 2) {
        if (n % p == 0) return false;
    }
    return true;
}

bool isPrime64(ull n) {
    if (n < 2) return false;
    if (!(n & 1)) return n == 2;

    int s = 0;
    ull d = n - 1;
    while (!(d & 1)) {
        d >>= 1;
        ++s;
    }

    constexpr ull bases[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    for (ull a : bases) {
        if (a % n == 0) continue;
        ull x = powMod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        for (int j = 1; j < s && x != n - 1; ++j) x = mulMod(x, x, n);
        if (x != n - 1) return false;
    }
    return true;
}

#include <utility>
#include <vector>

using ull = unsigned long long;

// In solve: ull n >= 1. factors stores (prime, exponent).
ull x = n;
std::vector<std::pair<ull, int>> factors;
for (ull p = 2; p <= x / p; p += p == 2 ? 1 : 2) {
    if (x % p) continue;
    int e = 0;
    do {
        x /= p;
        ++e;
    } while (x % p == 0);
    factors.emplace_back(p, e);
}
if (x > 1) factors.emplace_back(x, 1);

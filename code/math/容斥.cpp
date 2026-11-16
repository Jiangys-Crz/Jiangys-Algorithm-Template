#include <cstddef>
#include <numeric>
#include <vector>

using ull = unsigned long long;

// In solve: ull n and positive divisors d. Count their union in [1, n].
auto dfs = [&](auto&& self, std::size_t start, ull base) -> ull {
    ull count = 0;
    for (std::size_t i = start; i < d.size(); ++i) {
        ull q = d[i] / std::gcd(base, d[i]);
        if (base > n / q) continue;
        ull next = base * q;
        count += n / next - self(self, i + 1, next);
    }
    return count;
};
ull ans = dfs(dfs, 0, 1);

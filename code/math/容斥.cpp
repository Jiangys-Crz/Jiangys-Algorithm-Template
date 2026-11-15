#include <vector>

#include "euclid.hpp"

ull countMultiples(ull n, const std::vector<ull>& d) {
    auto dfs = [&](auto&& self, std::size_t start, ull base) -> ull {
        ull ans = 0;
        for (std::size_t i = start; i < d.size(); ++i) {
            ull q = d[i] / gcd(base, d[i]);
            if (base > n / q) continue;
            ull next = base * q;
            ans += n / next - self(self, i + 1, next);
        }
        return ans;
    };
    return dfs(dfs, 0, 1);
}

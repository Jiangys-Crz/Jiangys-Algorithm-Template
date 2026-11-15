#include <limits>
#include <optional>
#include <vector>

using ll = long long;
using ull = unsigned long long;

#ifndef XCPC_MATH_EUCLID_HPP
#define XCPC_MATH_EUCLID_HPP

constexpr ull gcd(ull a, ull b) {
    while (b) {
        ull r = a % b;
        a = b;
        b = r;
    }
    return a;
}

inline std::optional<ull> lcmChecked(ull a, ull b) {
    if (!a || !b) return 0;
    a /= gcd(a, b);
    if (a > std::numeric_limits<ull>::max() / b) return std::nullopt;
    return a * b;
}

inline ll exgcd(ll a, ll b, ll& x, ll& y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

#endif

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

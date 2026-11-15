#pragma once

#include <limits>
#include <optional>

#include "../types.hpp"

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

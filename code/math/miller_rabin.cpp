#include <limits>
#include <optional>

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

#ifndef XCPC_MATH_MOD_ARITHMETIC_HPP
#define XCPC_MATH_MOD_ARITHMETIC_HPP

constexpr ll safeMod(ll x, ll m) {
    ll r = x % m;
    return r < 0 ? r + m : r;
}

// a and b are reduced residues modulo m.
constexpr ull addMod(ull a, ull b, ull m) {
    return a >= m - b ? a - (m - b) : a + b;
}

constexpr ull mulMod(ull a, ull b, ull m) {
    a %= m;
    b %= m;
    if (m <= (ull{1} << 32)) return a * b % m;
    ull res = 0;
    while (b) {
        if (b & 1) res = addMod(res, a, m);
        b >>= 1;
        if (b) a = addMod(a, a, m);
    }
    return res;
}

constexpr ull powMod(ull a, ull b, ull m) {
    ull res = 1 % m;
    a %= m;
    while (b) {
        if (b & 1) res = mulMod(res, a, m);
        b >>= 1;
        if (b) a = mulMod(a, a, m);
    }
    return res;
}

inline std::optional<ll> invMod(ll a, ll m) {
    ll x, y;
    if (exgcd(safeMod(a, m), m, x, y) != 1) return std::nullopt;
    return safeMod(x, m);
}

#endif

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

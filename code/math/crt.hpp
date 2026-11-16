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

inline optional<ull> lcmChecked(ull a, ull b) {
    if (!a || !b) return 0;
    a /= gcd(a, b);
    if (a > numeric_limits<ull>::max() / b) return nullopt;
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

// a 和 b 已规约至 [0, m)。
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

inline optional<ll> invMod(ll a, ll m) {
    ll x, y;
    if (exgcd(safeMod(a, m), m, x, y) != 1) return nullopt;
    return safeMod(x, m);
}

#endif

#ifndef XCPC_MATH_CRT_HPP
#define XCPC_MATH_CRT_HPP

struct Congruence {
    ll r, mod;
};

enum class CRTStatus { ok, inconsistent, overflow, notCoprime };

struct CRTResult {
    CRTStatus status;
    Congruence value{0, 1};
};

inline CRTResult CRT(const vector<Congruence>& eqs) {
    ll m = 1;
    for (auto [r, mod] : eqs) {
        if (m > numeric_limits<ll>::max() / mod) return {CRTStatus::overflow};
        m *= mod;
    }
    ull ans = 0;
    for (auto [r, mod] : eqs) {
        if (mod == 1) continue;
        ll part = m / mod;
        auto inv = invMod(part, mod);
        if (!inv) return {CRTStatus::notCoprime};
        ull k = mulMod(safeMod(r, mod), *inv, mod);
        ans = addMod(ans, mulMod(part, k, m), m);
    }
    return {CRTStatus::ok, {static_cast<ll>(ans), m}};
}

inline CRTResult exCRT(const vector<Congruence>& eqs) {
    ll a = 0, m = 1;
    for (auto [r, mod] : eqs) {
        ll p, q;
        ll d = exgcd(m, mod, p, q);
        ll diff = safeMod(r, mod) - a;
        if (diff % d) return {CRTStatus::inconsistent};

        ll step = mod / d;
        if (m > numeric_limits<ll>::max() / step) {
            return {CRTStatus::overflow};
        }
        ll k = static_cast<ll>(mulMod(safeMod(p, step),
                                       safeMod(diff / d, step), step));
        a += m * k;
        m *= step;
    }
    return {CRTStatus::ok, {a, m}};
}

#endif

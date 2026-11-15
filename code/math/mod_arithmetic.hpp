#pragma once

#include "euclid.hpp"

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

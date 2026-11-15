#pragma once

#include <vector>

#include "mod_arithmetic.hpp"

struct Congruence {
    ll r, mod;
};

enum class CRTStatus { ok, inconsistent, overflow, notCoprime };

struct CRTResult {
    CRTStatus status;
    Congruence value{0, 1};
};

inline CRTResult CRT(const std::vector<Congruence>& eqs) {
    ll m = 1;
    for (auto [r, mod] : eqs) {
        if (m > std::numeric_limits<ll>::max() / mod) return {CRTStatus::overflow};
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

inline CRTResult exCRT(const std::vector<Congruence>& eqs) {
    ll a = 0, m = 1;
    for (auto [r, mod] : eqs) {
        ll p, q;
        ll d = exgcd(m, mod, p, q);
        ll diff = safeMod(r, mod) - a;
        if (diff % d) return {CRTStatus::inconsistent};

        ll step = mod / d;
        if (m > std::numeric_limits<ll>::max() / step) {
            return {CRTStatus::overflow};
        }
        ll k = static_cast<ll>(mulMod(safeMod(p, step),
                                       safeMod(diff / d, step), step));
        a += m * k;
        m *= step;
    }
    return {CRTStatus::ok, {a, m}};
}

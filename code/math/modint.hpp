#pragma once

#include <cassert>

#include "power.hpp"

template<uint P>
struct MInt {
    static_assert(P > 1);

    constexpr MInt(ll val = 0) {
        ll r = val % P;
        x = static_cast<uint>(r < 0 ? r + P : r);
    }

    static constexpr uint mod() { return P; }
    constexpr uint val() const { return x; }

    constexpr MInt& operator+=(MInt rhs) {
        ull v = ull(x) + rhs.x;
        x = v >= P ? v - P : v;
        return *this;
    }

    constexpr MInt& operator-=(MInt rhs) {
        x = x >= rhs.x ? x - rhs.x : P - (rhs.x - x);
        return *this;
    }

    constexpr MInt& operator*=(MInt rhs) {
        x = ull(x) * rhs.x % P;
        return *this;
    }

    constexpr MInt inv() const {
        assert(x != 0);
        return power(*this, P - 2);
    }

    constexpr MInt& operator/=(MInt rhs) { return *this *= rhs.inv(); }
    friend constexpr MInt operator+(MInt a, MInt b) { return a += b; }
    friend constexpr MInt operator-(MInt a, MInt b) { return a -= b; }
    friend constexpr MInt operator*(MInt a, MInt b) { return a *= b; }
    friend constexpr MInt operator/(MInt a, MInt b) { return a /= b; }
    friend constexpr bool operator==(MInt a, MInt b) { return a.x == b.x; }
    friend constexpr bool operator!=(MInt a, MInt b) { return !(a == b); }

private:
    uint x = 0;
};

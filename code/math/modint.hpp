#include <cassert>

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;

#ifndef XCPC_MATH_POWER_HPP
#define XCPC_MATH_POWER_HPP

template<class T>
constexpr T power(T a, ull b, T res = T{1}) {
    while (b) {
        if (b & 1) res = res * a;
        b >>= 1;
        if (b) a = a * a;
    }
    return res;
}

#endif

#ifndef XCPC_MATH_MODINT_HPP
#define XCPC_MATH_MODINT_HPP

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

#endif

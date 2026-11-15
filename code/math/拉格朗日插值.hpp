#include <cassert>
#include <vector>

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

#ifndef XCPC_MATH_COMB_HPP
#define XCPC_MATH_COMB_HPP

template<class Z>
struct Comb {
    int n = 0;
    std::vector<Z> _fac{1}, _invfac{1};

    explicit Comb(int m = 0) { init(m); }

    void init(int m) {
        if (m <= n) return;
        assert(static_cast<unsigned>(m) < Z::mod());
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        for (int i = n + 1; i <= m; ++i) _fac[i] = _fac[i - 1] * i;
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; --i) _invfac[i - 1] = _invfac[i] * i;
        n = m;
    }

    Z fac(int m) const { return _fac[m]; }
    Z invfac(int m) const { return _invfac[m]; }

    Z C(int m, int k) const {
        if (k < 0 || k > m) return 0;
        assert(m <= n);
        return fac(m) * invfac(k) * invfac(m - k);
    }

    Z A(int m, int k) const {
        if (k < 0 || k > m) return 0;
        assert(m <= n);
        return fac(m) * invfac(m - k);
    }
};

#endif

#ifndef XCPC_MATH_LAGRANGE_INTERPOLATION_HPP
#define XCPC_MATH_LAGRANGE_INTERPOLATION_HPP

template<class Z>
Z lagrangeConsecutive(const std::vector<Z>& y, Z x, const Comb<Z>& comb) {
    int n = static_cast<int>(y.size()) - 1;
    if (x.val() < y.size()) return y[x.val()];

    std::vector<Z> pre(n + 2, 1), suf(n + 2, 1);
    for (int i = 0; i <= n; ++i) pre[i + 1] = pre[i] * (x - i);
    for (int i = n; i >= 0; --i) suf[i] = suf[i + 1] * (x - i);

    Z res = 0;
    for (int i = 0; i <= n; ++i) {
        Z term = y[i] * pre[i] * suf[i + 1] *
                 comb.invfac(i) * comb.invfac(n - i);
        if ((n - i) & 1) res -= term;
        else res += term;
    }
    return res;
}

#endif

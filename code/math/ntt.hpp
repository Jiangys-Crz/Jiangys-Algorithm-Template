using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;

#ifndef XCPC_MATH_BIT_REVERSE_HPP
#define XCPC_MATH_BIT_REVERSE_HPP

template<class T>
void bitReverse(vector<T>& a) {
    auto n = a.size();
    assert(n && !(n & (n - 1)));
    for (size_t i = 1, j = 0; i < n; ++i) {
        size_t bit = n / 2;
        while (j & bit) {
            j ^= bit;
            bit >>= 1;
        }
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
}

#endif

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

#ifndef XCPC_MATH_NTT_HPP
#define XCPC_MATH_NTT_HPP

struct NTT {
    using Z = MInt<998244353>;

    static void dft(vector<Z>& a, bool inverse = false) {
        auto n = a.size();
        assert(n && (Z::mod() - 1) % n == 0);
        bitReverse(a);
        for (size_t len = 2; len <= n; len *= 2) {
            Z wn = power(Z{3}, (Z::mod() - 1) / len);
            if (inverse) wn = wn.inv();
            for (size_t i = 0; i < n; i += len) {
                Z w = 1;
                for (size_t j = 0; j < len / 2; ++j) {
                    Z x = a[i + j], y = a[i + j + len / 2] * w;
                    a[i + j] = x + y;
                    a[i + j + len / 2] = x - y;
                    w *= wn;
                }
            }
        }
        if (inverse) {
            Z inv = Z(n).inv();
            for (Z& x : a) x *= inv;
        }
    }

    static vector<Z> convolution(vector<Z> a, vector<Z> b) {
        if (a.empty() || b.empty()) return {};
        size_t need = a.size() + b.size() - 1, n = 1;
        assert(need <= (size_t{1} << 23));
        while (n < need) n *= 2;
        a.resize(n);
        b.resize(n);
        dft(a);
        dft(b);
        for (size_t i = 0; i < n; ++i) a[i] *= b[i];
        dft(a, true);
        a.resize(need);
        return a;
    }
};

#endif

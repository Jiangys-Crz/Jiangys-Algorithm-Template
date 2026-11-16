#include <cassert>
#include <cmath>
#include <complex>
#include <utility>
#include <vector>

using ll = long long;

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

using Complex = complex<long double>;

void fft(vector<Complex>& a, bool inverse = false) {
    bitReverse(a);
    const long double pi = acos(-1.0L);
    auto n = a.size();
    for (size_t len = 2; len <= n; len *= 2) {
        long double angle = (inverse ? -2.0L : 2.0L) * pi / len;
        Complex wn = polar(1.0L, angle);
        for (size_t i = 0; i < n; i += len) {
            Complex w = 1;
            for (size_t j = 0; j < len / 2; ++j) {
                auto x = a[i + j], y = a[i + j + len / 2] * w;
                a[i + j] = x + y;
                a[i + j + len / 2] = x - y;
                w *= wn;
            }
        }
    }
    if (inverse) {
        for (auto& x : a) x /= static_cast<long double>(n);
    }
}

vector<ll> convolutionFFT(const vector<ll>& a,
                                const vector<ll>& b) {
    if (a.empty() || b.empty()) return {};
    size_t need = a.size() + b.size() - 1, n = 1;
    while (n < need) n *= 2;
    vector<Complex> f(a.begin(), a.end()), g(b.begin(), b.end());
    f.resize(n);
    g.resize(n);
    fft(f);
    fft(g);
    for (size_t i = 0; i < n; ++i) f[i] *= g[i];
    fft(f, true);
    vector<ll> res(need);
    for (size_t i = 0; i < need; ++i) res[i] = llround(f[i].real());
    return res;
}

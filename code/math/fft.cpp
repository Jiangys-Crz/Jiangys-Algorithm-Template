#include <cmath>
#include <complex>

#include "bit_reverse.hpp"
#include "euclid.hpp"

using Complex = std::complex<long double>;

void fft(std::vector<Complex>& a, bool inverse = false) {
    bitReverse(a);
    const long double pi = std::acos(-1.0L);
    auto n = a.size();
    for (std::size_t len = 2; len <= n; len *= 2) {
        long double angle = (inverse ? -2.0L : 2.0L) * pi / len;
        Complex wn = std::polar(1.0L, angle);
        for (std::size_t i = 0; i < n; i += len) {
            Complex w = 1;
            for (std::size_t j = 0; j < len / 2; ++j) {
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

std::vector<ll> convolutionFFT(const std::vector<ll>& a,
                                const std::vector<ll>& b) {
    if (a.empty() || b.empty()) return {};
    std::size_t need = a.size() + b.size() - 1, n = 1;
    while (n < need) n *= 2;
    std::vector<Complex> f(a.begin(), a.end()), g(b.begin(), b.end());
    f.resize(n);
    g.resize(n);
    fft(f);
    fft(g);
    for (std::size_t i = 0; i < n; ++i) f[i] *= g[i];
    fft(f, true);
    std::vector<ll> res(need);
    for (std::size_t i = 0; i < need; ++i) res[i] = std::llround(f[i].real());
    return res;
}

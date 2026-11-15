#pragma once

#include "bit_reverse.hpp"
#include "modint.hpp"

struct NTT {
    using Z = MInt<998244353>;

    static void dft(std::vector<Z>& a, bool inverse = false) {
        auto n = a.size();
        assert(n && (Z::mod() - 1) % n == 0);
        bitReverse(a);
        for (std::size_t len = 2; len <= n; len *= 2) {
            Z wn = power(Z{3}, (Z::mod() - 1) / len);
            if (inverse) wn = wn.inv();
            for (std::size_t i = 0; i < n; i += len) {
                Z w = 1;
                for (std::size_t j = 0; j < len / 2; ++j) {
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

    static std::vector<Z> convolution(std::vector<Z> a, std::vector<Z> b) {
        if (a.empty() || b.empty()) return {};
        std::size_t need = a.size() + b.size() - 1, n = 1;
        assert(need <= (std::size_t{1} << 23));
        while (n < need) n *= 2;
        a.resize(n);
        b.resize(n);
        dft(a);
        dft(b);
        for (std::size_t i = 0; i < n; ++i) a[i] *= b[i];
        dft(a, true);
        a.resize(need);
        return a;
    }
};

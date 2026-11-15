#pragma once

#include <cassert>
#include <vector>

#include "modint.hpp"

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

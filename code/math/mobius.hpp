#pragma once

#include <algorithm>

#include "euclid.hpp"
#include "linear_sieve.hpp"

struct MobiusPrefix {
    std::vector<int> pre;

    explicit MobiusPrefix(const LinearSieve& sieve) : pre(sieve.mu.size()) {
        for (std::size_t i = 1; i < pre.size(); ++i) {
            pre[i] = pre[i - 1] + sieve.mu[i];
        }
    }

    ll countCoprimePairs(int n, int m) const {
        ll res = 0;
        int end = std::min(n, m);
        for (int l = 1; l <= end; ) {
            int x = n / l, y = m / l;
            int r = std::min(n / x, m / y);
            res += ll(pre[r] - pre[l - 1]) * x * y;
            if (r == end) break;
            l = r + 1;
        }
        return res;
    }
};

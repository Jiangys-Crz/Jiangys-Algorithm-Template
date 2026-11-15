#pragma once

#include <utility>
#include <vector>

#include "euclid.hpp"

inline std::vector<std::pair<ull, int>> factorize(ull n) {
    std::vector<std::pair<ull, int>> res;
    for (ull p = 2; p <= n / p; p += p == 2 ? 1 : 2) {
        if (n % p != 0) continue;
        int e = 0;
        do {
            n /= p;
            ++e;
        } while (n % p == 0);
        res.push_back({p, e});
    }
    if (n > 1) res.push_back({n, 1});
    return res;
}

inline ull eulerPhi(ull n) {
    ull res = n;
    for (auto [p, e] : factorize(n)) res -= res / p;
    return res;
}

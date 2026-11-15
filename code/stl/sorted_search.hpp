#pragma once

#include <algorithm>
#include <utility>
#include <vector>

#include "../types.hpp"

inline std::pair<int, int> equalIndices(const std::vector<ll>& a, ll x) {
    auto l = std::lower_bound(a.begin(), a.end(), x);
    auto r = std::upper_bound(l, a.end(), x);
    return {static_cast<int>(l - a.begin()), static_cast<int>(r - a.begin())};
}

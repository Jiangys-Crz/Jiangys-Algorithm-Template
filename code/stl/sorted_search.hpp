#include <algorithm>
#include <utility>
#include <vector>

using ll = long long;

#ifndef XCPC_STL_SORTED_SEARCH_HPP
#define XCPC_STL_SORTED_SEARCH_HPP

inline std::pair<int, int> equalIndices(const std::vector<ll>& a, ll x) {
    auto l = std::lower_bound(a.begin(), a.end(), x);
    auto r = std::upper_bound(l, a.end(), x);
    return {static_cast<int>(l - a.begin()), static_cast<int>(r - a.begin())};
}

#endif

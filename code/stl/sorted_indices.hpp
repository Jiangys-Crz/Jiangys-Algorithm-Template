#include <algorithm>
#include <numeric>
#include <vector>

using ll = long long;

#ifndef XCPC_STL_SORTED_INDICES_HPP
#define XCPC_STL_SORTED_INDICES_HPP

inline std::vector<int> sortedIndices(const std::vector<ll>& a) {
    std::vector<int> id(a.size());
    std::iota(id.begin(), id.end(), 0);
    std::sort(id.begin(), id.end(), [&](int i, int j) {
        if (a[i] != a[j]) return a[i] < a[j];
        return i < j;
    });
    return id;
}

#endif

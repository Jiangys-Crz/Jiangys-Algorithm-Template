#include <algorithm>
#include <cstddef>
#include <optional>
#include <vector>

using ll = long long;

#ifndef XCPC_STL_KTH_SMALLEST_HPP
#define XCPC_STL_KTH_SMALLEST_HPP

inline std::optional<ll> kthSmallest(std::vector<ll> a, int k) {
    if (k <= 0 || static_cast<std::size_t>(k) > a.size()) return std::nullopt;
    auto it = a.begin() + (k - 1);
    std::nth_element(a.begin(), it, a.end());
    return *it;
}

#endif

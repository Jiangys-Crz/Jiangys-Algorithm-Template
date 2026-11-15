#include <bitset>
#include <cstddef>
#include <vector>

#ifndef XCPC_DS_BITSET_SUBSET_SUM_HPP
#define XCPC_DS_BITSET_SUBSET_SUM_HPP

template<std::size_t MAX>
std::bitset<MAX + 1> reachableSums(const std::vector<int>& a) {
    std::bitset<MAX + 1> dp;
    dp[0] = true;
    for (int x : a) dp |= dp << static_cast<std::size_t>(x);
    return dp;
}

#endif

#include <limits>

using uint = unsigned int;
using ull = unsigned long long;

#ifndef XCPC_STL_BIT_OPS_HPP
#define XCPC_STL_BIT_OPS_HPP

inline int popcount32(uint x) {
    return __builtin_popcount(x);
}

inline int popcount64(ull x) {
    return __builtin_popcountll(x);
}

inline int ctz32(uint x) {
    return x ? __builtin_ctz(x) : std::numeric_limits<uint>::digits;
}

inline int ctz64(ull x) {
    return x ? __builtin_ctzll(x) : std::numeric_limits<ull>::digits;
}

inline int clz32(uint x) {
    return x ? __builtin_clz(x) : std::numeric_limits<uint>::digits;
}

inline int clz64(ull x) {
    return x ? __builtin_clzll(x) : std::numeric_limits<ull>::digits;
}

#endif

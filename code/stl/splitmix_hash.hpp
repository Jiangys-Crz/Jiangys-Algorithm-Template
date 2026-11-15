#include <chrono>
#include <cstddef>

using ull = unsigned long long;

#ifndef XCPC_STL_SPLITMIX_HASH_HPP
#define XCPC_STL_SPLITMIX_HASH_HPP

struct SplitMix64Hash {
    static ull mix(ull x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }

    std::size_t operator()(ull x) const {
        static const ull seed = static_cast<ull>(
            std::chrono::steady_clock::now().time_since_epoch().count());
        return static_cast<std::size_t>(mix(x + seed));
    }
};

#endif

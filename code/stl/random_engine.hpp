#include <algorithm>
#include <random>

using uint = unsigned int;
using ll = long long;

#ifndef XCPC_STL_RANDOM_ENGINE_HPP
#define XCPC_STL_RANDOM_ENGINE_HPP

struct RandomEngine {
    std::mt19937 rng;

    explicit RandomEngine(uint seed = std::random_device{}()) : rng(seed) {}

    ll next(ll l, ll r) {
        return std::uniform_int_distribution<ll>(l, r)(rng);
    }

    template<class It>
    void shuffle(It first, It last) {
        std::shuffle(first, last, rng);
    }
};

#endif

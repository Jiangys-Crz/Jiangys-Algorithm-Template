#pragma once

#include <algorithm>
#include <random>

#include "../types.hpp"

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

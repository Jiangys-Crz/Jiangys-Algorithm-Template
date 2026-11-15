#include <algorithm>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

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

#ifndef XCPC_ZX_RANDOM_CASES_HPP
#define XCPC_ZX_RANDOM_CASES_HPP

inline std::vector<ll> randomArray(RandomEngine& rng, int n, ll lo, ll hi) {
    std::vector<ll> a(n);
    for (ll& x : a) x = rng.next(lo, hi);
    return a;
}

inline std::vector<int> randomPermutation(RandomEngine& rng, int n) {
    std::vector<int> a(n);
    std::iota(a.begin(), a.end(), 1LL);
    rng.shuffle(a.begin(), a.end());
    return a;
}

inline std::vector<std::pair<int, int>> randomTree(RandomEngine& rng, int n) {
    auto id = randomPermutation(rng, n);
    std::vector<std::pair<int, int>> edges;
    if (n > 0) edges.reserve(n - 1);
    for (int i = 1; i < n; ++i) {
        int p = static_cast<int>(rng.next(0, i - 1));
        edges.emplace_back(id[p], id[i]);
    }
    rng.shuffle(edges.begin(), edges.end());
    return edges;
}

#endif

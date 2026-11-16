#include <algorithm>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

using uint = unsigned int;
using ll = long long;

// In solve: uint seed, int n >= 1 and ll l <= r.
// Reuse the engine for all draws in a test case.
std::mt19937 rng(seed);

std::vector<ll> a(n);
std::uniform_int_distribution<ll> pick(l, r);
for (ll& x : a) x = pick(rng);

std::vector<int> id(n);
std::iota(id.begin(), id.end(), 1LL);
std::shuffle(id.begin(), id.end(), rng);

std::vector<std::pair<int, int>> edges;
for (int i = 1; i < n; ++i) {
    int p = std::uniform_int_distribution<int>(0, i - 1)(rng);
    edges.emplace_back(id[p], id[i]);
}
// TODO: Write only the structures needed by the problem's input format.

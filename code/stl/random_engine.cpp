#include <algorithm>
#include <random>

using uint = unsigned int;
using ll = long long;

// In solve: uint seed, ll l <= r, and a sequence a to shuffle.
std::mt19937 rng(seed);
std::uniform_int_distribution<ll> pick(l, r);
ll x = pick(rng);
std::shuffle(a.begin(), a.end(), rng);

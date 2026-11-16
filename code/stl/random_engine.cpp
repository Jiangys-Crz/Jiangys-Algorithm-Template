#include <algorithm>
#include <random>

using uint = unsigned int;
using ll = long long;

// 先准备随机种子 seed、取样区间 [l, r] 和待打乱的序列 a。
mt19937 rng(seed);
uniform_int_distribution<ll> pick(l, r);
ll x = pick(rng);
shuffle(a.begin(), a.end(), rng);

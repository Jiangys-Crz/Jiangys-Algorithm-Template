#include <limits>

using ull = unsigned long long;

// In solve: ull x. For x == 0, trailing and leading equal the bit width.

constexpr int width = std::numeric_limits<ull>::digits;
int ones = __builtin_popcountll(x);
int trailing = x ? __builtin_ctzll(x) : width;
int leading = x ? __builtin_clzll(x) : width;

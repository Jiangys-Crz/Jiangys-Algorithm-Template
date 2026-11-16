#include <limits>

using ull = unsigned long long;

// x 为 64 位无符号整数。x == 0 时，尾零数和前导零数均取位宽。

constexpr int width = numeric_limits<ull>::digits;
int ones = __builtin_popcountll(x);
int trailing = x ? __builtin_ctzll(x) : width;
int leading = x ? __builtin_clzll(x) : width;

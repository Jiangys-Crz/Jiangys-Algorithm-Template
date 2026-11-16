#include <bitset>

// In solve: a contains nonnegative weights.
// Keep reachable sums in [0, maxSum].

constexpr int maxSum = /* TODO: largest sum to keep */;
std::bitset<maxSum + 1> dp;
dp[0] = true;
for (int x : a) dp |= dp << x;

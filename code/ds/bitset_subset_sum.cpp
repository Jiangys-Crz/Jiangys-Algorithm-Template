// 数组 a 存放非负重量。
// 仅保留 [0, maxSum] 内的可达和。

constexpr int maxSum = /* 待填写：需要保留的最大和 */;
bitset<maxSum + 1> dp;
dp[0] = true;
for (int x : a) dp |= dp << x;

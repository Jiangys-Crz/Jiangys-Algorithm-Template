#include <vector>

using ll = long long;

// 先准备长度为 n 的数组 a，下标从 1 开始。查询采用闭区间 [l, r]。
vector<ll> suf(n + 2);
for (int i = n; i >= 1; --i) suf[i] = a[i] + suf[i + 1];

ll ans = suf[l] - suf[r + 1];

using ll = long long;

// 先准备长度为 n 的数组 a，下标从 1 开始。查询采用闭区间 [l, r]。
vector<ll> pre(n + 1);
for (int i = 1; i <= n; ++i) pre[i] = pre[i - 1] + a[i];

ll ans = pre[r] - pre[l - 1];

#include <vector>

using ll = long long;

// In solve: int n and vector<ll> a indexed 1..n; query [l, r].
std::vector<ll> pre(n + 1);
for (int i = 1; i <= n; ++i) pre[i] = pre[i - 1] + a[i];

ll ans = pre[r] - pre[l - 1];

#include <vector>

using ll = long long;

// In solve: int n and vector<ll> a indexed 1..n; query [l, r].
std::vector<ll> suf(n + 2);
for (int i = n; i >= 1; --i) suf[i] = a[i] + suf[i + 1];

ll ans = suf[l] - suf[r + 1];

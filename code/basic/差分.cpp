#include <tuple>
#include <vector>

using ll = long long;

// In solve: int n; a[0] = 0, a[1..n] are the original values.
// updates contains tuples (l, r, delta) for closed intervals.
std::vector<ll> d(n + 2);
for (int i = 1; i <= n; ++i) d[i] = a[i] - a[i - 1];

for (auto [l, r, delta] : updates) {
    d[l] += delta;
    d[r + 1] -= delta;
}
for (int i = 1; i <= n; ++i) d[i] += d[i - 1];
// d[1..n] now stores the updated values.

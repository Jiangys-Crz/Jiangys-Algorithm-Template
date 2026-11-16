#include <vector>

using ll = long long;

// In solve: int n, ll x, sorted vector<ll> a indexed 1..n.
// Use ans as the boundary index; 0 and n + 1 are sentinels.

int l = 0, r = n;
while (l < r) {
    int mid = r - (r - l) / 2;
    if (a[mid] <= x) l = mid;
    else r = mid - 1;
}
int ans = l;

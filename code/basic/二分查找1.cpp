#include <vector>

using ll = long long;

// In solve: int n, ll x, sorted vector<ll> a indexed 1..n.
// Use ans as the boundary index; 0 and n + 1 are sentinels.

int l = 1, r = n + 1;
while (l < r) {
    int mid = l + (r - l) / 2;
    if (a[mid] >= x) r = mid;
    else l = mid + 1;
}
int ans = l;

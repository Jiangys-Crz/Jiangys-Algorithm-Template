#include <vector>

using ll = long long;
using lll = __int128;

// In solve: sorted vector<ll> a and ll target.

int l = 0, r = static_cast<int>(a.size()) - 1;
while (l < r) {
    lll sum = lll(a[l]) + a[r];
    if (sum == target) break;
    if (sum < target) ++l;
    else --r;
}
// If l < r, (l, r) is a valid pair; otherwise no pair exists.

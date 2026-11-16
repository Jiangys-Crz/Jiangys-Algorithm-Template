#include <algorithm>
#include <vector>

using ll = long long;

// In solve: vector<ll> a and 1 <= k <= a.size().
// The contents of a may be reordered.

auto it = a.begin() + (k - 1);
std::nth_element(a.begin(), it, a.end());
ll ans = *it;

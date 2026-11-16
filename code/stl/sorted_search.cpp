#include <algorithm>
#include <vector>

using ll = long long;

// In solve: nondecreasing vector<ll> a and ll x.

auto l = std::lower_bound(a.begin(), a.end(), x);
auto r = std::upper_bound(l, a.end(), x);
auto first = l - a.begin(), last = r - a.begin();

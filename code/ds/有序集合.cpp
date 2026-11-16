#include <iterator>
#include <set>

using ll = long long;

// In solve: multiset<ll> s and ll x. Erase at most one occurrence.

auto it = s.find(x);
if (it != s.end()) s.erase(it);

auto l = s.lower_bound(x);
auto r = s.upper_bound(x);
// Strict predecessor exists if l != s.begin(); it is *std::prev(l).
// Strict successor exists if r != s.end(); it is *r.

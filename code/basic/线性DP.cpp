#include <algorithm>

using ll = long long;

// In solve: vector<ll> a. oneBack is the maximum non-adjacent sum.

ll twoBack = 0, oneBack = 0;
for (ll x : a) {
    ll cur = std::max(oneBack, twoBack + x);
    twoBack = oneBack;
    oneBack = cur;
}

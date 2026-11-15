#include <algorithm>
#include <vector>

using ll = long long;

ll maxNonAdjacentSum(const std::vector<ll>& a) {
    ll twoBack = 0, oneBack = 0;
    for (ll value : a) {
        ll current = std::max(oneBack, twoBack + value);
        twoBack = oneBack;
        oneBack = current;
    }
    return oneBack;
}

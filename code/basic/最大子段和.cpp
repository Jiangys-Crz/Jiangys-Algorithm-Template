#include <algorithm>
#include <cstddef>
#include <vector>

using ll = long long;

ll maxSubarraySum(const std::vector<ll>& a) {
    ll ending = a.front(), best = ending;
    for (std::size_t i = 1; i < a.size(); ++i) {
        ending = a[i] + std::max(0LL, ending);
        best = std::max(best, ending);
    }
    return best;
}

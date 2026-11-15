#include <algorithm>
#include <cstddef>
#include <vector>

long long maxSubarraySum(const std::vector<long long>& a) {
    long long ending = a.front(), best = ending;
    for (std::size_t i = 1; i < a.size(); ++i) {
        ending = a[i] + std::max(0LL, ending);
        best = std::max(best, ending);
    }
    return best;
}

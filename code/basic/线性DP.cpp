#include <algorithm>
#include <vector>

long long maxNonAdjacentSum(const std::vector<long long>& a) {
    long long twoBack = 0, oneBack = 0;
    for (long long value : a) {
        long long current = std::max(oneBack, twoBack + value);
        twoBack = oneBack;
        oneBack = current;
    }
    return oneBack;
}

#include <algorithm>
#include <vector>

std::vector<long long> sortedUnique(std::vector<long long> values) {
    std::sort(values.begin(), values.end());
    values.erase(std::unique(values.begin(), values.end()), values.end());
    return values;
}

int compressedRank(const std::vector<long long>& values, long long x) {
    auto it = std::lower_bound(values.begin(), values.end(), x);
    if (it == values.end() || *it != x) {
        return 0;
    }
    return static_cast<int>(it - values.begin()) + 1;
}

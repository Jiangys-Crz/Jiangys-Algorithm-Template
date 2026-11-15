#include <algorithm>
#include <vector>

using ll = long long;

std::vector<ll> sortedUnique(std::vector<ll> values) {
    std::sort(values.begin(), values.end());
    values.erase(std::unique(values.begin(), values.end()), values.end());
    return values;
}

int compressedRank(const std::vector<ll>& values, ll x) {
    auto it = std::lower_bound(values.begin(), values.end(), x);
    if (it == values.end() || *it != x) {
        return 0;
    }
    return static_cast<int>(it - values.begin()) + 1;
}

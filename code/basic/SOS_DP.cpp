#include <cstddef>
#include <vector>

using ll = long long;

// In solve: int n and vector<ll> values of length 2^n.
// After the loops values[mask] is the sum over all submasks.

for (int bit = 0; bit < n; ++bit) {
    const std::size_t flag = std::size_t{1} << bit;
    for (std::size_t mask = 0; mask < values.size(); ++mask) {
        if ((mask & flag) != 0) {
            values[mask] += values[mask ^ flag];
        }
    }
}

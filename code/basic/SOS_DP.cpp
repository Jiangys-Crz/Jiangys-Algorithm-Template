#include <cstddef>
#include <vector>

// values has length 2^n. All intermediate sums fit in long long.
std::vector<long long> sumOverSubsets(std::vector<long long> values, int n) {
    for (int bit = 0; bit < n; ++bit) {
        const std::size_t flag = std::size_t{1} << bit;
        for (std::size_t mask = 0; mask < values.size(); ++mask) {
            if ((mask & flag) != 0) {
                values[mask] += values[mask ^ flag];
            }
        }
    }
    return values;
}

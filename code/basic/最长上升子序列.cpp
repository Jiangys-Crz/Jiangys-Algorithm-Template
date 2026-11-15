#include <algorithm>
#include <cstddef>
#include <vector>

std::size_t lisLength(const std::vector<long long>& a) {
    std::vector<long long> tails;
    for (long long value : a) {
        auto it = std::lower_bound(tails.begin(), tails.end(), value);
        if (it == tails.end()) tails.push_back(value);
        else *it = value;
    }
    return tails.size();
}

#include <algorithm>
#include <cstddef>
#include <vector>

#include "../types.hpp"

std::size_t lisLength(const std::vector<ll>& a) {
    std::vector<ll> tails;
    for (ll value : a) {
        auto it = std::lower_bound(tails.begin(), tails.end(), value);
        if (it == tails.end()) tails.push_back(value);
        else *it = value;
    }
    return tails.size();
}

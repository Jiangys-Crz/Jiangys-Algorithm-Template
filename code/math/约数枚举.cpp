#include <vector>

#include "euclid.hpp"

std::vector<ull> divisors(ull n) {
    std::vector<ull> small, large;
    for (ull d = 1; d <= n / d; ++d) {
        if (n % d != 0) continue;
        small.push_back(d);
        if (d != n / d) large.push_back(n / d);
    }
    small.insert(small.end(), large.rbegin(), large.rend());
    return small;
}

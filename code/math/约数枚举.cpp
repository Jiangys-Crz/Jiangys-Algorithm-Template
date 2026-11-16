#include <vector>

using ull = unsigned long long;

// In solve: ull n >= 1. divisors is in increasing order.

std::vector<ull> small, large;
for (ull d = 1; d <= n / d; ++d) {
    if (n % d != 0) continue;
    small.push_back(d);
    if (d != n / d) large.push_back(n / d);
}
small.insert(small.end(), large.rbegin(), large.rend());
const auto& divisors = small;

#include <cstddef>
#include <vector>

using ull = unsigned long long;

// In solve: vector<ull> a and the 0-based, half-open query [l, r).
std::vector<ull> p(a.size() + 1);
for (std::size_t i = 0; i < a.size(); ++i) p[i + 1] = p[i] ^ a[i];
ull ans = p[r] ^ p[l];

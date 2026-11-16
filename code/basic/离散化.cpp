#include <algorithm>
#include <vector>

using ll = long long;

// In solve: vals contains all values to compress; x is a queried value.
std::sort(vals.begin(), vals.end());
vals.erase(std::unique(vals.begin(), vals.end()), vals.end());

auto it = std::lower_bound(vals.begin(), vals.end(), x);
auto rank = it != vals.end() && *it == x ? it - vals.begin() + 1 : 0;

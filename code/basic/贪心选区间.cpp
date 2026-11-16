#include <algorithm>
#include <limits>
#include <utility>
#include <vector>

using ll = long long;

// In solve: vector<pair<ll, ll>> a of half-open intervals [l, r), l < r.

std::sort(a.begin(), a.end(), [](const auto& x, const auto& y) {
    return x.second < y.second;
});

int ans = 0;
ll last = std::numeric_limits<ll>::min();
for (auto [l, r] : a) {
    if (l >= last) {
        ++ans;
        last = r;
    }
}

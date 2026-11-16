#include <algorithm>

using ll = long long;

// In solve: nonempty vector<ll> a.

ll ending = a.front(), ans = ending;
for (std::size_t i = 1; i < a.size(); ++i) {
    ending = a[i] + std::max(0LL, ending);
    ans = std::max(ans, ending);
}

#include <vector>

using ll = long long;

// In solve: vector<ll> a, int n = a.size().
// prev[i] is the index of the closest strictly smaller value on the left.

std::vector<int> stk, prev(n, -1);
for (int i = 0; i < n; ++i) {
    while (!stk.empty() && a[stk.back()] >= a[i]) stk.pop_back();
    if (!stk.empty()) prev[i] = stk.back();
    stk.push_back(i);
}

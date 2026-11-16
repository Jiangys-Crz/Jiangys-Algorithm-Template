#include <deque>
#include <vector>

using ll = long long;

// In solve: vector<ll> a, length n and window width 1 <= k <= n.
// ans stores the minimum of each complete window.

std::deque<int> q;
std::vector<ll> ans;
for (int i = 0; i < n; ++i) {
    while (!q.empty() && q.front() <= i - k) q.pop_front();
    while (!q.empty() && a[q.back()] >= a[i]) q.pop_back();
    q.push_back(i);
    if (i + 1 >= k) ans.push_back(a[q.front()]);
}

#include <deque>
#include <vector>

using ll = long long;

std::vector<ll> slidingMin(const std::vector<ll>& a, int k) {
    int n = static_cast<int>(a.size());
    if (k <= 0 || k > n) return {};

    std::deque<int> q;
    std::vector<ll> ans;
    for (int i = 0; i < n; ++i) {
        while (!q.empty() && q.front() <= i - k) q.pop_front();
        while (!q.empty() && a[q.back()] >= a[i]) q.pop_back();
        q.push_back(i);
        if (i + 1 >= k) ans.push_back(a[q.front()]);
    }
    return ans;
}

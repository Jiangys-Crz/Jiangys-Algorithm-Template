#include <iostream>
#include <deque>
#include <vector>

using ll = long long;

int main() {
    int n, k;
    if (!(std::cin >> n >> k)) return 0;
    if (k <= 0 || k > n) {
        std::cout << '\n';
        return 0;
    }
    std::vector<ll> a(n);
    for (ll& x : a) std::cin >> x;

    std::deque<int> q;
    for (int i = 0; i < n; ++i) {
        while (!q.empty() && q.front() <= i - k) q.pop_front();
        while (!q.empty() && a[q.back()] >= a[i]) q.pop_back();
        q.push_back(i);
        if (i + 1 >= k) std::cout << a[q.front()] << (i + 1 == n ? '\n' : ' ');
    }
}

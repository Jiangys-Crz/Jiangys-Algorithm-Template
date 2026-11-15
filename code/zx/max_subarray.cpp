#include <algorithm>
#include <iostream>
#include <vector>

using ll = long long;

ll solve(const std::vector<ll>& a) {
    ll ans = a.front();
#ifdef BRUTE
    for (std::size_t l = 0; l < a.size(); ++l) {
        ll sum = 0;
        for (std::size_t r = l; r < a.size(); ++r) {
            sum += a[r];
            ans = std::max(ans, sum);
        }
    }
#else
    ll pre = 0, low = 0;
    for (ll x : a) {
        pre += x;
        ans = std::max(ans, pre - low);
        low = std::min(low, pre);
    }
#endif
    return ans;
}

int main() {
    int n;
    if (!(std::cin >> n) || n <= 0) return 1;
    std::vector<ll> a(n);
    for (ll& x : a) {
        if (!(std::cin >> x)) return 1;
    }
    std::cout << solve(a) << '\n';
}

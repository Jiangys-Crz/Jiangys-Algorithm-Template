#include <algorithm>
#include <iostream>
#include <vector>

using ll = long long;

int main() {
    int n;
    ll limit;
    if (!(std::cin >> n >> limit)) return 0;
    std::vector<ll> a(n);
    for (ll& x : a) std::cin >> x;

    int l = 0, ans = 0;
    ll sum = 0;
    for (int r = 0; r < n; ++r) {
        sum += a[r];
        while (l <= r && sum > limit) sum -= a[l++];
        ans = std::max(ans, r - l + 1);
    }
    std::cout << ans << '\n';
}

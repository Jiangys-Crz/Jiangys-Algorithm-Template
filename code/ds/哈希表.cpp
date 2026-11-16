#include <cstddef>
#include <iostream>
#include <limits>
#include <unordered_map>

using ll = long long;

int main() {
    int n;
    ll target;
    if (!(std::cin >> n >> target)) return 0;
    std::unordered_map<ll, ll> cnt;
    cnt.reserve(static_cast<std::size_t>(n) + 1);
    cnt[0] = 1;

    ll sum = 0, ans = 0;
    for (int i = 0; i < n; ++i) {
        ll x;
        std::cin >> x;
        sum += x;
        if ((target >= 0 || sum <= std::numeric_limits<ll>::max() + target) &&
            (target <= 0 || sum >= std::numeric_limits<ll>::min() + target)) {
            auto it = cnt.find(sum - target);
            if (it != cnt.end()) ans += it->second;
        }
        ++cnt[sum];
    }
    std::cout << ans << '\n';
}

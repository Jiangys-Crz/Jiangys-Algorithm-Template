#include <limits>
#include <unordered_map>
#include <vector>

using ll = long long;

ll countTargetSum(const std::vector<ll>& a, ll target) {
    std::unordered_map<ll, ll> cnt;
    cnt.reserve(a.size() + 1);
    cnt[0] = 1;

    ll sum = 0, ans = 0;
    for (ll x : a) {
        sum += x;
        if ((target >= 0 || sum <= std::numeric_limits<ll>::max() + target) &&
            (target <= 0 || sum >= std::numeric_limits<ll>::min() + target)) {
            auto it = cnt.find(sum - target);
            if (it != cnt.end()) ans += it->second;
        }
        ++cnt[sum];
    }
    return ans;
}

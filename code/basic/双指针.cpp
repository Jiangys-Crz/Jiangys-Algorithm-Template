#include <utility>
#include <vector>

using ll = long long;

std::pair<int, int> findPairSum(const std::vector<int>& a, ll target) {
    int l = 0, r = static_cast<int>(a.size()) - 1;
    while (l < r) {
        ll sum = static_cast<ll>(a[l]) + a[r];
        if (sum == target) {
            return {l, r};
        }
        if (sum < target) {
            ++l;
        } else {
            --r;
        }
    }
    return {-1, -1};
}

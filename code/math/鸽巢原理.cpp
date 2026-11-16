#include <utility>
#include <vector>

using ll = long long;

// In solve: vector<ll> a. range is 0-based and half-open.
int n = static_cast<int>(a.size());
std::pair<int, int> range{0, 0};
if (n > 0) {
    std::vector<int> first(n, -1);
    first[0] = 0;
    ll rem = 0;
    for (int i = 0; i < n; ++i) {
        rem = (rem + a[i] % n) % n;
        if (rem < 0) rem += n;
        if (first[rem] != -1) {
            range = {first[rem], i + 1};
            break;
        }
        first[rem] = i + 1;
    }
}

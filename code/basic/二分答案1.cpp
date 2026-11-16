#include <iostream>

using ll = long long;
using lll = __int128;

int main() {
    ll n;
    if (!(std::cin >> n)) return 0;
    ll l = 0, r = n;
    while (l < r) {
        ll mid = l + (r - l) / 2;
        if (lll(mid) * mid >= n) r = mid;
        else l = mid + 1;
    }
    std::cout << l << '\n';
}

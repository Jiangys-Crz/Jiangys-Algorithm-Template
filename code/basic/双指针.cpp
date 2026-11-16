#include <iostream>
#include <vector>

using ll = long long;
using lll = __int128;

int main() {
    int n;
    ll target;
    if (!(std::cin >> n >> target)) return 0;
    std::vector<ll> a(n);
    for (ll& x : a) std::cin >> x;

    int l = 0, r = n - 1;
    while (l < r) {
        lll sum = lll(a[l]) + a[r];
        if (sum == target) break;
        if (sum < target) ++l;
        else --r;
    }
    if (l < r) std::cout << l << ' ' << r << '\n';
    else std::cout << "-1 -1\n";
}

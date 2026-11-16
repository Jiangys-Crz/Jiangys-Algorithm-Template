#include <iostream>
#include <vector>

using ll = long long;

int main() {
    int n;
    ll x;
    if (!(std::cin >> n >> x)) return 0;
    std::vector<ll> a(n + 1);
    for (int i = 1; i <= n; ++i) std::cin >> a[i];

    int l = 0, r = n;
    while (l < r) {
        int mid = r - (r - l) / 2;
        if (a[mid] <= x) l = mid;
        else r = mid - 1;
    }
    std::cout << l << '\n';
}

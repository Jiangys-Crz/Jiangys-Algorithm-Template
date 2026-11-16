#include <iostream>
#include <vector>

using ll = long long;

int main() {
    int n;
    ll x;
    if (!(std::cin >> n >> x)) return 0;
    std::vector<ll> a(n + 1);
    for (int i = 1; i <= n; ++i) std::cin >> a[i];

    int l = 1, r = n + 1;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (a[mid] >= x) r = mid;
        else l = mid + 1;
    }
    std::cout << l << '\n';
}

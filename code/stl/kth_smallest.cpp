#include <algorithm>
#include <iostream>
#include <vector>

using ll = long long;

int main() {
    int n, k;
    if (!(std::cin >> n >> k)) return 0;
    std::vector<ll> a(n);
    for (ll& v : a) std::cin >> v;
    if (k < 1 || k > n) {
        std::cout << "NONE\n";
        return 0;
    }

    auto it = a.begin() + (k - 1);
    std::nth_element(a.begin(), it, a.end());
    std::cout << *it << '\n';
}

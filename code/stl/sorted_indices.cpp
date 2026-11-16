#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using ll = long long;

int main() {
    int n;
    if (!(std::cin >> n)) return 0;
    std::vector<ll> a(n);
    for (ll& x : a) std::cin >> x;
    std::vector<int> id(n);
    std::iota(id.begin(), id.end(), 0);
    std::sort(id.begin(), id.end(), [&](int i, int j) {
        if (a[i] != a[j]) return a[i] < a[j];
        return i < j;
    });
    for (int i : id) std::cout << i << ' ';
    std::cout << '\n';
}

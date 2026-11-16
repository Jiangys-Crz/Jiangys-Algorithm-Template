#include <iostream>
#include <vector>

using ll = long long;

int main() {
    int n;
    if (!(std::cin >> n)) return 0;
    std::vector<ll> a(n);
    for (ll& x : a) std::cin >> x;
    std::vector<int> stk;
    for (int i = 0; i < n; ++i) {
        while (!stk.empty() && a[stk.back()] >= a[i]) stk.pop_back();
        std::cout << (stk.empty() ? -1 : stk.back()) << (i + 1 == n ? '\n' : ' ');
        stk.push_back(i);
    }
}

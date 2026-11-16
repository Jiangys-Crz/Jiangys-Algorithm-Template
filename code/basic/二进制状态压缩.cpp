#include <iostream>

using ull = unsigned long long;

int main() {
    int n, m;
    if (!(std::cin >> n >> m)) return 0;
    ull a = 0, b = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        a |= 1ULL << x;
    }
    for (int i = 0; i < m; ++i) {
        int x;
        std::cin >> x;
        b |= 1ULL << x;
    }
    std::cout << ((a & b) == b) << ' ' << ((a & b) == 0) << '\n';
}

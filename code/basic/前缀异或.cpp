#include <iostream>
#include <vector>

using ull = unsigned long long;

int main() {
    int n, q;
    if (!(std::cin >> n >> q)) return 0;
    std::vector<ull> p(n + 1);
    for (int i = 0; i < n; ++i) {
        ull x;
        std::cin >> x;
        p[i + 1] = p[i] ^ x;
    }

    while (q--) {
        int l, r;
        std::cin >> l >> r;
        std::cout << (p[r] ^ p[l]) << '\n';
    }
}

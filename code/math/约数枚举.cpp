#include <iostream>
#include <vector>

using ull = unsigned long long;

int main() {
    ull n;
    if (!(std::cin >> n)) return 0;

    std::vector<ull> small, large;
    for (ull d = 1; d <= n / d; ++d) {
        if (n % d != 0) continue;
        small.push_back(d);
        if (d != n / d) large.push_back(n / d);
    }
    for (ull d : small) std::cout << d << ' ';
    for (auto it = large.rbegin(); it != large.rend(); ++it) std::cout << *it << ' ';
    std::cout << '\n';
}

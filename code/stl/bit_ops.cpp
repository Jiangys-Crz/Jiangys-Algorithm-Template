#include <iostream>
#include <limits>

using ull = unsigned long long;

int main() {
    ull x;
    if (!(std::cin >> x)) return 0;
    constexpr int width = std::numeric_limits<ull>::digits;
    int ones = __builtin_popcountll(x);
    int trailing = x ? __builtin_ctzll(x) : width;
    int leading = x ? __builtin_clzll(x) : width;
    std::cout << ones << ' ' << trailing << ' ' << leading << '\n';
}

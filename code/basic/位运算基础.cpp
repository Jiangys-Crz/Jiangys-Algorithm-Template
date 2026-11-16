#include <iostream>

using ull = unsigned long long;

int main() {
    ull mask;
    int bit;
    if (!(std::cin >> mask >> bit)) return 0;
    ull flag = 1ULL << bit;
    std::cout << bool(mask & flag) << ' ' << (mask | flag) << ' '
              << (mask & ~flag) << ' ' << (mask ^ flag) << '\n';
}

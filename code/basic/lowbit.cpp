#include <iostream>

using ull = unsigned long long;

int main() {
    ull x;
    if (!(std::cin >> x)) return 0;
    std::cout << (x & -x) << '\n';

    int count = 0;
    while (x) {
        x -= x & -x;
        ++count;
    }
    std::cout << count << '\n';
}

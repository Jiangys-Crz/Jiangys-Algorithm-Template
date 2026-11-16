#include <iostream>

using ull = unsigned long long;

int main() {
    ull a, b;
    if (!(std::cin >> a >> b)) return 0;
    while (b) {
        ull r = a % b;
        a = b;
        b = r;
    }
    std::cout << a << '\n';
}

#include <iostream>

using ull = unsigned long long;

int main() {
    ull mask;
    if (!(std::cin >> mask)) return 0;
    for (ull s = mask; ; s = (s - 1) & mask) {
        std::cout << s << (s == 0 ? '\n' : ' ');
        if (s == 0) break;
    }
}

#include <iostream>
#include <algorithm>
#include <cstddef>
#include <string>

int main() {
    std::string s;
    if (!std::getline(std::cin, s)) return 0;
    auto n = s.size();
    if (!n) {
        std::cout << "0\n";
        return 0;
    }

    std::size_t i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        unsigned char a = s[(i + k) % n], b = s[(j + k) % n];
        if (a == b) {
            ++k;
        } else {
            if (a > b) i += k + 1;
            else j += k + 1;
            if (i == j) ++j;
            k = 0;
        }
    }
    std::cout << std::min(i, j) << '\n';
}

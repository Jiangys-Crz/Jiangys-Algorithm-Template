#include <cstddef>
#include <iostream>
#include <string>

int main() {
    std::string s;
    if (!std::getline(std::cin, s)) return 0;
    for (std::size_t l = 0; ; ) {
        auto r = s.find(',', l);
        if (r == std::string::npos) {
            std::cout << s.substr(l) << '\n';
            break;
        }
        std::cout << s.substr(l, r - l) << '\n';
        l = r + 1;
    }
}

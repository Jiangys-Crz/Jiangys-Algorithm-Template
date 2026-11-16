#include <iostream>
#include <cstddef>
#include <string>

int main() {
    std::string pattern, text;
    if (!std::getline(std::cin, pattern) || !std::getline(std::cin, text)) return 0;
    std::size_t j = 0;
    for (char c : text) {
        if (j < pattern.size() && c == pattern[j]) ++j;
    }
    std::cout << (j == pattern.size()) << '\n';
}

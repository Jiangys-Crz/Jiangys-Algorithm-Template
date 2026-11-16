#include <iostream>
#include <algorithm>
#include <limits>
#include <string>
#include <vector>

int main() {
    int n;
    if (!(std::cin >> n)) return 0;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::vector<std::string> a(n);
    for (auto& s : a) std::getline(std::cin, s);

    std::sort(a.begin(), a.end(), [](const std::string& x, const std::string& y) {
        if (x.empty() != y.empty()) return x.empty();
        for (std::size_t i = 0; i < x.size() + y.size(); ++i) {
            unsigned char u = i < x.size() ? x[i] : y[i - x.size()];
            unsigned char v = i < y.size() ? y[i] : x[i - y.size()];
            if (u != v) return u < v;
        }
        return false;
    });
    for (const auto& s : a) std::cout << s;
    std::cout << '\n';
}

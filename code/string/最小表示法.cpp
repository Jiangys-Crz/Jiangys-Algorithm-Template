#include <algorithm>
#include <cstddef>
#include <string_view>

std::size_t minimumRotation(std::string_view s) {
    auto n = s.size();
    if (!n) return 0;

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
    return std::min(i, j);
}

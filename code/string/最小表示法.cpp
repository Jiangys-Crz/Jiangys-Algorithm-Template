#include <algorithm>
#include <cstddef>
#include <string>

// In solve: string or string_view s. pos is the first minimum rotation index.

auto n = s.size();
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
auto pos = std::min(i, j);

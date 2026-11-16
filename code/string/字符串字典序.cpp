#include <algorithm>
#include <limits>
#include <string>
#include <vector>

// In solve: vector<string> a. Concatenating sorted a gives the smallest string.

std::sort(a.begin(), a.end(), [](const std::string& x, const std::string& y) {
    if (x.empty() != y.empty()) return x.empty();
    for (std::size_t i = 0; i < x.size() + y.size(); ++i) {
        unsigned char u = i < x.size() ? x[i] : y[i - x.size()];
        unsigned char v = i < y.size() ? y[i] : x[i - y.size()];
        if (u != v) return u < v;
    }
    return false;
});

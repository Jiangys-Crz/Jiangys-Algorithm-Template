#include "prefix_function.hpp"

struct StringPeriod {
    int step, block;
};

StringPeriod stringPeriod(std::string_view s) {
    if (s.empty()) return {0, 0};
    int n = static_cast<int>(s.size());
    int p = n - prefixFunction(s).back();
    return {p, n % p == 0 ? p : n};
}

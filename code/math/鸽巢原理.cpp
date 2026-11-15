#include <utility>
#include <vector>

#include "mod_arithmetic.hpp"

std::pair<int, int> divisibleSubarray(const std::vector<ll>& a) {
    int n = static_cast<int>(a.size());
    if (!n) return {0, 0};
    std::vector<int> first(n, -1);
    first[0] = 0;
    ull r = 0;
    for (int i = 0; i < n; ++i) {
        r = addMod(r, safeMod(a[i], n), n);
        if (first[r] != -1) return {first[r], i + 1};
        first[r] = i + 1;
    }
    return {0, 0};
}

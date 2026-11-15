#pragma once

#include <optional>
#include <vector>

#include "point.hpp"

template<class T>
struct HullDiameter {
    Point<T> a, b;
    T dist2;
};

template<class T>
std::optional<HullDiameter<T>> convexDiameter(const std::vector<Point<T>>& h) {
    int n = static_cast<int>(h.size());
    if (!n) return std::nullopt;

    HullDiameter<T> ans{h.front(), h.back(), dist2(h.front(), h.back())};
    if (n <= 2) return ans;

    auto relax = [&](int i, int j) {
        T d = dist2(h[i], h[j]);
        if (d > ans.dist2) ans = {h[i], h[j], d};
    };
    for (int i = 0, j = 1; i < n; ++i) {
        int k = (i + 1) % n;
        auto area = [&](int t) { return cross(h[i], h[k], h[t]); };
        while (area((j + 1) % n) > area(j)) j = (j + 1) % n;
        relax(i, j);
        relax(k, j);
        if (area((j + 1) % n) == area(j)) {
            relax(i, (j + 1) % n);
            relax(k, (j + 1) % n);
        }
    }
    return ans;
}

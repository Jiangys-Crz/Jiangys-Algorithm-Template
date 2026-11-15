#pragma once

#include <algorithm>
#include <vector>

#include "polar_order.hpp"

namespace geometry_detail {
template<class T>
void hullPush(std::vector<Point<T>>& h, Point<T> p) {
    while (h.size() >= 2 && cross(h[h.size() - 2], h.back(), p) <= T{}) {
        h.pop_back();
    }
    h.push_back(p);
}
}

template<class T>
std::vector<Point<T>> convexHullAndrew(std::vector<Point<T>> p) {
    std::sort(p.begin(), p.end());
    p.erase(std::unique(p.begin(), p.end()), p.end());
    if (p.size() <= 1) return p;

    std::vector<Point<T>> lo, hi;
    for (auto q : p) geometry_detail::hullPush(lo, q);
    for (auto it = p.rbegin(); it != p.rend(); ++it) {
        geometry_detail::hullPush(hi, *it);
    }
    lo.pop_back();
    hi.pop_back();
    lo.insert(lo.end(), hi.begin(), hi.end());
    return lo;
}

template<class T>
std::vector<Point<T>> convexHullGraham(std::vector<Point<T>> p) {
    if (p.size() <= 1) return p;
    auto first = std::min_element(p.begin(), p.end(), [](auto a, auto b) {
        return a.y < b.y || (a.y == b.y && a.x < b.x);
    });
    std::iter_swap(p.begin(), first);
    auto o = p.front();
    std::sort(p.begin() + 1, p.end(), [o](auto a, auto b) {
        return PolarLess<T>{}(a - o, b - o);
    });
    p.erase(std::unique(p.begin(), p.end()), p.end());

    std::vector<Point<T>> h;
    for (auto q : p) geometry_detail::hullPush(h, q);
    return h;
}

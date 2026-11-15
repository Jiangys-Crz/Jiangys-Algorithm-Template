#pragma once

#include <vector>

#include "segment.hpp"

template<class T>
T signedArea2(const std::vector<Point<T>>& p) {
    T ans{};
    for (std::size_t i = 1; i + 1 < p.size(); ++i) {
        ans += cross(p[0], p[i], p[i + 1]);
    }
    return ans;
}

enum class PointLocation { outside, boundary, inside };

template<class T>
PointLocation pointInPolygon(Point<T> q, const std::vector<Point<T>>& p) {
    bool inside = false;
    for (std::size_t i = 0; i < p.size(); ++i) {
        auto a = p[i], b = p[(i + 1) % p.size()];
        if (pointOnSegment(q, Line<T>{a, b})) return PointLocation::boundary;

        T c = cross(a, b, q);
        if (a.y <= q.y && q.y < b.y && c > T{}) inside = !inside;
        if (b.y <= q.y && q.y < a.y && c < T{}) inside = !inside;
    }
    return inside ? PointLocation::inside : PointLocation::outside;
}

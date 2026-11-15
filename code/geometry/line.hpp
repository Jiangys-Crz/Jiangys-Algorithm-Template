#pragma once

#include <optional>

#include "precision.hpp"

template<class T>
std::optional<Real> pointLineDistance(Point<T> p, Line<T> l) {
    auto d = static_cast<RealPoint>(l.b - l.a);
    Real len = length(d);
    if (len == 0) return std::nullopt;
    return std::abs(cross(d / len, static_cast<RealPoint>(p - l.a)));
}

enum class LineRelation { point, parallel, coincident, degenerate };

struct LineHit {
    LineRelation kind;
    RealPoint p{};
};

inline LineHit lineIntersection(Line<Real> l, Line<Real> r,
                                Real angleTol = eps, Real distTol = eps) {
    auto u = l.b - l.a, v = r.b - r.a;
    Real lu = length(u), lv = length(v);
    if (lu == 0 || lv == 0) return {LineRelation::degenerate};

    u = u / lu;
    v = v / lv;
    auto w = r.a - l.a;
    Real den = cross(u, v);
    if (!sign(den, angleTol)) {
        return {sign(cross(u, w), distTol) ? LineRelation::parallel
                                          : LineRelation::coincident};
    }
    return {LineRelation::point, l.a + u * (cross(w, v) / den)};
}

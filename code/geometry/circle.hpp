#pragma once

#include <array>
#include <utility>

#include "line.hpp"

struct Circle {
    RealPoint o;
    Real r;
};

enum class CircleRelation { none, one, two, coincident, degenerate };

struct CircleHit {
    CircleRelation kind;
    std::array<RealPoint, 2> p{};
};

inline CircleHit circleLineIntersection(Circle c, Line<Real> l,
                                        Real absTol = eps, Real relTol = eps) {
    auto u = l.b - l.a;
    Real len = length(u);
    if (len == 0) return {CircleRelation::degenerate};
    u = u / len;

    Real h = cross(u, l.a - c.o);
    Real d = std::abs(h);
    int cmp = dcmp(d, c.r, absTol, relTol);
    if (cmp > 0) return {CircleRelation::none};

    auto foot = c.o + rotate90(u) * h;
    if (!cmp) return {CircleRelation::one, {c.r == 0 ? c.o : foot}};
    Real t = std::sqrt(std::max(Real{}, (c.r - d) * (c.r + d)));
    return {CircleRelation::two, {foot - u * t, foot + u * t}};
}

inline CircleHit circleIntersection(Circle a, Circle b,
                                    Real absTol = eps, Real relTol = eps) {
    auto v = b.o - a.o;
    Real d = length(v);
    if (a.r == 0 && b.r == 0) {
        if (a.o == b.o) return {CircleRelation::one, {a.o}};
        return {CircleRelation::none};
    }
    if (a.r == 0 || b.r == 0) {
        if (b.r == 0) std::swap(a, b);
        if (!dcmp(d, b.r, absTol, relTol)) return {CircleRelation::one, {a.o}};
        return {CircleRelation::none};
    }
    if (d == 0) {
        return {dcmp(a.r, b.r, absTol, relTol) ? CircleRelation::none
                                               : CircleRelation::coincident};
    }

    Real sum = a.r + b.r, gap = std::abs(a.r - b.r);
    int outer = dcmp(d, sum, absTol, relTol);
    int inner = dcmp(d, gap, absTol, relTol);
    if (outer > 0 || inner < 0) return {CircleRelation::none};

    auto u = v / d;
    if (!outer || (!inner && gap > 0)) {
        Real t = !outer || a.r > b.r ? a.r : -a.r;
        return {CircleRelation::one, {a.o + u * t}};
    }

    Real t = (d + (a.r - b.r) / d * sum) / 2;
    auto mid = a.o + u * t;
    Real h = std::sqrt(std::max(Real{}, (a.r - t) * (a.r + t)));
    auto delta = rotate90(u) * h;
    return {CircleRelation::two, {mid - delta, mid + delta}};
}

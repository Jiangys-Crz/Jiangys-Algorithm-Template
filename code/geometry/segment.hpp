#pragma once

#include "precision.hpp"

template<class T>
bool pointOnSegment(Point<T> p, Line<T> s) {
    return cross(s.a, s.b, p) == T{} &&
           !(p < std::min(s.a, s.b)) && !(std::max(s.a, s.b) < p);
}

enum class SegmentRelation { disjoint, proper, touch, overlap };

template<class T>
struct SegmentHit {
    SegmentRelation kind;
    Point<T> a{}, b{};
};

template<class T>
SegmentHit<T> segmentIntersection(Line<T> s, Line<T> t) {
    int a = sgn(cross(s.a, s.b, t.a)), b = sgn(cross(s.a, s.b, t.b));
    int c = sgn(cross(t.a, t.b, s.a)), d = sgn(cross(t.a, t.b, s.b));
    if (!a && !b && !c && !d) {
        auto l = std::max(std::min(s.a, s.b), std::min(t.a, t.b));
        auto r = std::min(std::max(s.a, s.b), std::max(t.a, t.b));
        if (r < l) return {SegmentRelation::disjoint};
        return {l == r ? SegmentRelation::touch : SegmentRelation::overlap, l, r};
    }

    if (a * b < 0 && c * d < 0) return {SegmentRelation::proper};
    if (!a && pointOnSegment(t.a, s)) return {SegmentRelation::touch, t.a, t.a};
    if (!b && pointOnSegment(t.b, s)) return {SegmentRelation::touch, t.b, t.b};
    if (!c && pointOnSegment(s.a, t)) return {SegmentRelation::touch, s.a, s.a};
    if (!d && pointOnSegment(s.b, t)) return {SegmentRelation::touch, s.b, s.b};
    return {SegmentRelation::disjoint};
}

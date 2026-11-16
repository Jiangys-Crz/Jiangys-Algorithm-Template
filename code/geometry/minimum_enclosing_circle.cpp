#include <algorithm>
#include <array>
#include <cmath>
#include <optional>
#include <random>
#include <utility>
#include <vector>

using ull = unsigned long long;

#ifndef XCPC_GEOMETRY_POINT_HPP
#define XCPC_GEOMETRY_POINT_HPP

using Real = long double;

template<class T>
struct Point {
    T x{}, y{};

    constexpr Point(T x = T{}, T y = T{}) : x(x), y(y) {}

    template<class U>
    explicit constexpr operator Point<U>() const {
        return {static_cast<U>(x), static_cast<U>(y)};
    }

    friend constexpr Point operator+(Point a, Point b) {
        return {a.x + b.x, a.y + b.y};
    }

    friend constexpr Point operator-(Point a, Point b) {
        return {a.x - b.x, a.y - b.y};
    }

    friend constexpr Point operator*(Point a, T k) {
        return {a.x * k, a.y * k};
    }

    friend constexpr Point operator/(Point a, T k) {
        return {a.x / k, a.y / k};
    }

    friend constexpr bool operator==(Point a, Point b) {
        return a.x == b.x && a.y == b.y;
    }

    friend constexpr bool operator<(Point a, Point b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    }
};

using RealPoint = Point<Real>;

template<class T>
constexpr T dot(Point<T> a, Point<T> b) {
    return a.x * b.x + a.y * b.y;
}

template<class T>
constexpr T cross(Point<T> a, Point<T> b) {
    return a.x * b.y - a.y * b.x;
}

template<class T>
constexpr T cross(Point<T> a, Point<T> b, Point<T> c) {
    return cross(b - a, c - a);
}

template<class T>
constexpr T square(Point<T> p) {
    return dot(p, p);
}

template<class T>
constexpr T dist2(Point<T> a, Point<T> b) {
    return square(a - b);
}

template<class T>
Real length(Point<T> p) {
    return hypot(static_cast<Real>(p.x), static_cast<Real>(p.y));
}

template<class T>
Real dist(Point<T> a, Point<T> b) {
    return length(a - b);
}

template<class T>
constexpr Point<T> rotate90(Point<T> p) {
    return {-p.y, p.x};
}

template<class T>
struct Line {
    Point<T> a, b;
};

#endif

#ifndef XCPC_GEOMETRY_PRECISION_HPP
#define XCPC_GEOMETRY_PRECISION_HPP

inline constexpr Real eps = 1e-12L;

template<class T>
constexpr int sgn(T x) {
    return (x > T{}) - (x < T{});
}

inline int sign(Real x, Real tol = eps) {
    return (x > tol) - (x < -tol);
}

inline int dcmp(Real a, Real b, Real absTol = eps, Real relTol = eps) {
    Real scale = max(abs(a), abs(b));
    return sign(a - b, max(absTol, relTol * scale));
}

#endif

#ifndef XCPC_GEOMETRY_LINE_HPP
#define XCPC_GEOMETRY_LINE_HPP

template<class T>
optional<Real> pointLineDistance(Point<T> p, Line<T> l) {
    auto d = static_cast<RealPoint>(l.b - l.a);
    Real len = length(d);
    if (len == 0) return nullopt;
    return abs(cross(d / len, static_cast<RealPoint>(p - l.a)));
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

#endif

#ifndef XCPC_GEOMETRY_CIRCLE_HPP
#define XCPC_GEOMETRY_CIRCLE_HPP

struct Circle {
    RealPoint o;
    Real r;
};

enum class CircleRelation { none, one, two, coincident, degenerate };

struct CircleHit {
    CircleRelation kind;
    array<RealPoint, 2> p{};
};

inline CircleHit circleLineIntersection(Circle c, Line<Real> l,
                                        Real absTol = eps, Real relTol = eps) {
    auto u = l.b - l.a;
    Real len = length(u);
    if (len == 0) return {CircleRelation::degenerate};
    u = u / len;

    Real h = cross(u, l.a - c.o);
    Real d = abs(h);
    int cmp = dcmp(d, c.r, absTol, relTol);
    if (cmp > 0) return {CircleRelation::none};

    auto foot = c.o + rotate90(u) * h;
    if (!cmp) return {CircleRelation::one, {c.r == 0 ? c.o : foot}};
    Real t = sqrt(max(Real{}, (c.r - d) * (c.r + d)));
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
        if (b.r == 0) swap(a, b);
        if (!dcmp(d, b.r, absTol, relTol)) return {CircleRelation::one, {a.o}};
        return {CircleRelation::none};
    }
    if (d == 0) {
        return {dcmp(a.r, b.r, absTol, relTol) ? CircleRelation::none
                                               : CircleRelation::coincident};
    }

    Real sum = a.r + b.r, gap = abs(a.r - b.r);
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
    Real h = sqrt(max(Real{}, (a.r - t) * (a.r + t)));
    auto delta = rotate90(u) * h;
    return {CircleRelation::two, {mid - delta, mid + delta}};
}

#endif

namespace geometry_detail {
Circle diameterCircle(RealPoint a, RealPoint b) {
    return {a + (b - a) / 2, dist(a, b) / 2};
}

Circle throughThree(RealPoint a, RealPoint b, RealPoint c) {
    auto u = b - a, v = c - a;
    Real d = 2 * cross(u, v);
    if (d == 0) {
        array<Circle, 3> cand{diameterCircle(a, b), diameterCircle(a, c),
                                   diameterCircle(b, c)};
        return *max_element(cand.begin(), cand.end(), [](Circle x, Circle y) {
            return x.r < y.r;
        });
    }
    auto off = (rotate90(u) * square(v) - rotate90(v) * square(u)) / d;
    return {a + off, max({length(off), length(off - u), length(off - v)})};
}
}

optional<Circle> minEnclosingCircle(
    vector<RealPoint> p, ull seed = random_device{}(), Real tol = eps) {
    if (p.empty()) return nullopt;
    mt19937_64 rng(seed);
    shuffle(p.begin(), p.end(), rng);

    Circle c{p.front(), 0};
    auto contains = [&](RealPoint q) {
        return dcmp(dist(c.o, q), c.r, tol, tol) <= 0;
    };
    for (size_t i = 0; i < p.size(); ++i) {
        if (contains(p[i])) continue;
        c = {p[i], 0};
        for (size_t j = 0; j < i; ++j) {
            if (contains(p[j])) continue;
            c = geometry_detail::diameterCircle(p[i], p[j]);
            for (size_t k = 0; k < j; ++k) {
                if (!contains(p[k])) {
                    c = geometry_detail::throughThree(p[i], p[j], p[k]);
                }
            }
        }
    }
    for (auto q : p) c.r = max(c.r, dist(c.o, q));
    return c;
}

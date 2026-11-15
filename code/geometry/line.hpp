#include <algorithm>
#include <cmath>
#include <optional>

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
    return std::hypot(static_cast<Real>(p.x), static_cast<Real>(p.y));
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
    Real scale = std::max(std::abs(a), std::abs(b));
    return sign(a - b, std::max(absTol, relTol * scale));
}

#endif

#ifndef XCPC_GEOMETRY_LINE_HPP
#define XCPC_GEOMETRY_LINE_HPP

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

#endif

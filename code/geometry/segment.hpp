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

#ifndef XCPC_GEOMETRY_SEGMENT_HPP
#define XCPC_GEOMETRY_SEGMENT_HPP

template<class T>
bool pointOnSegment(Point<T> p, Line<T> s) {
    return cross(s.a, s.b, p) == T{} &&
           !(p < min(s.a, s.b)) && !(max(s.a, s.b) < p);
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
        auto l = max(min(s.a, s.b), min(t.a, t.b));
        auto r = min(max(s.a, s.b), max(t.a, t.b));
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

#endif

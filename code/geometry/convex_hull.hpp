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

#ifndef XCPC_GEOMETRY_POLAR_ORDER_HPP
#define XCPC_GEOMETRY_POLAR_ORDER_HPP

template<class T>
struct PolarLess {
    bool operator()(Point<T> a, Point<T> b) const {
        bool za = a == Point<T>{}, zb = b == Point<T>{};
        if (za || zb) return za && !zb;
        if (half(a) != half(b)) return half(a) < half(b);

        T c = cross(a, b);
        if (c != T{}) return c > T{};
        return square(a) < square(b);
    }

private:
    static int half(Point<T> p) {
        return p.y > T{} || (p.y == T{} && p.x > T{}) ? 0 : 1;
    }
};

#endif

#ifndef XCPC_GEOMETRY_CONVEX_HULL_HPP
#define XCPC_GEOMETRY_CONVEX_HULL_HPP

namespace geometry_detail {
template<class T>
void hullPush(vector<Point<T>>& h, Point<T> p) {
    while (h.size() >= 2 && cross(h[h.size() - 2], h.back(), p) <= T{}) {
        h.pop_back();
    }
    h.push_back(p);
}
}

template<class T>
vector<Point<T>> convexHullAndrew(vector<Point<T>> p) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    if (p.size() <= 1) return p;

    vector<Point<T>> lo, hi;
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
vector<Point<T>> convexHullGraham(vector<Point<T>> p) {
    if (p.size() <= 1) return p;
    auto first = min_element(p.begin(), p.end(), [](auto a, auto b) {
        return a.y < b.y || (a.y == b.y && a.x < b.x);
    });
    iter_swap(p.begin(), first);
    auto o = p.front();
    sort(p.begin() + 1, p.end(), [o](auto a, auto b) {
        return PolarLess<T>{}(a - o, b - o);
    });
    p.erase(unique(p.begin(), p.end()), p.end());

    vector<Point<T>> h;
    for (auto q : p) geometry_detail::hullPush(h, q);
    return h;
}

#endif

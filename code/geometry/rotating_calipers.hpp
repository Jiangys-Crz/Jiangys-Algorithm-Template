#include <cmath>
#include <optional>
#include <vector>

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

#ifndef XCPC_GEOMETRY_ROTATING_CALIPERS_HPP
#define XCPC_GEOMETRY_ROTATING_CALIPERS_HPP

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

#endif

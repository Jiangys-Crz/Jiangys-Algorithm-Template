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

#ifndef XCPC_GEOMETRY_CLOSEST_PAIR_HPP
#define XCPC_GEOMETRY_CLOSEST_PAIR_HPP

template<class T>
struct ClosestPair {
    Point<T> a, b;
    T dist2;
};

template<class T>
optional<ClosestPair<T>> closestPair(vector<Point<T>> a) {
    int n = static_cast<int>(a.size());
    if (n < 2) return nullopt;
    sort(a.begin(), a.end());
    vector<Point<T>> tmp(n);

    auto byY = [](Point<T> p, Point<T> q) {
        return p.y < q.y || (p.y == q.y && p.x < q.x);
    };
    auto relax = [](ClosestPair<T>& ans, Point<T> p, Point<T> q) {
        T d = dist2(p, q);
        if (d < ans.dist2) ans = {p, q, d};
    };
    auto dfs = [&](auto&& self, int l, int r) -> ClosestPair<T> {
        if (r - l <= 3) {
            ClosestPair<T> ans{a[l], a[l + 1], dist2(a[l], a[l + 1])};
            if (r - l == 3) {
                relax(ans, a[l], a[l + 2]);
                relax(ans, a[l + 1], a[l + 2]);
            }
            sort(a.begin() + l, a.begin() + r, byY);
            return ans;
        }

        int mid = l + (r - l) / 2;
        T x = a[mid].x;
        auto ans = self(self, l, mid), right = self(self, mid, r);
        if (right.dist2 < ans.dist2) ans = right;
        merge(a.begin() + l, a.begin() + mid, a.begin() + mid,
                   a.begin() + r, tmp.begin() + l, byY);
        copy(tmp.begin() + l, tmp.begin() + r, a.begin() + l);

        int k = l;
        for (int i = l; i < r; ++i) {
            T dx = a[i].x - x;
            if (dx * dx >= ans.dist2) continue;
            for (int j = k - 1; j >= l; --j) {
                T dy = a[i].y - tmp[j].y;
                if (dy * dy >= ans.dist2) break;
                relax(ans, a[i], tmp[j]);
            }
            tmp[k++] = a[i];
        }
        return ans;
    };
    return dfs(dfs, 0, n);
}

#endif

#pragma once

#include <algorithm>
#include <optional>
#include <vector>

#include "point.hpp"

template<class T>
struct ClosestPair {
    Point<T> a, b;
    T dist2;
};

template<class T>
std::optional<ClosestPair<T>> closestPair(std::vector<Point<T>> a) {
    int n = static_cast<int>(a.size());
    if (n < 2) return std::nullopt;
    std::sort(a.begin(), a.end());
    std::vector<Point<T>> tmp(n);

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
            std::sort(a.begin() + l, a.begin() + r, byY);
            return ans;
        }

        int mid = l + (r - l) / 2;
        T x = a[mid].x;
        auto ans = self(self, l, mid), right = self(self, mid, r);
        if (right.dist2 < ans.dist2) ans = right;
        std::merge(a.begin() + l, a.begin() + mid, a.begin() + mid,
                   a.begin() + r, tmp.begin() + l, byY);
        std::copy(tmp.begin() + l, tmp.begin() + r, a.begin() + l);

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

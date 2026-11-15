#include <random>
#include <vector>

#include "circle.hpp"

namespace geometry_detail {
Circle diameterCircle(RealPoint a, RealPoint b) {
    return {a + (b - a) / 2, dist(a, b) / 2};
}

Circle throughThree(RealPoint a, RealPoint b, RealPoint c) {
    auto u = b - a, v = c - a;
    Real d = 2 * cross(u, v);
    if (d == 0) {
        std::array<Circle, 3> cand{diameterCircle(a, b), diameterCircle(a, c),
                                   diameterCircle(b, c)};
        return *std::max_element(cand.begin(), cand.end(), [](Circle x, Circle y) {
            return x.r < y.r;
        });
    }
    auto off = (rotate90(u) * square(v) - rotate90(v) * square(u)) / d;
    return {a + off, std::max({length(off), length(off - u), length(off - v)})};
}
}

std::optional<Circle> minEnclosingCircle(
    std::vector<RealPoint> p, ull seed = std::random_device{}(), Real tol = eps) {
    if (p.empty()) return std::nullopt;
    std::mt19937_64 rng(seed);
    std::shuffle(p.begin(), p.end(), rng);

    Circle c{p.front(), 0};
    auto contains = [&](RealPoint q) {
        return dcmp(dist(c.o, q), c.r, tol, tol) <= 0;
    };
    for (std::size_t i = 0; i < p.size(); ++i) {
        if (contains(p[i])) continue;
        c = {p[i], 0};
        for (std::size_t j = 0; j < i; ++j) {
            if (contains(p[j])) continue;
            c = geometry_detail::diameterCircle(p[i], p[j]);
            for (std::size_t k = 0; k < j; ++k) {
                if (!contains(p[k])) {
                    c = geometry_detail::throughThree(p[i], p[j], p[k]);
                }
            }
        }
    }
    for (auto q : p) c.r = std::max(c.r, dist(c.o, q));
    return c;
}

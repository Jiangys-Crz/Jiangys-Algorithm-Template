#pragma once

#include <algorithm>

#include "covered_length.hpp"

template<class T>
struct Rectangle {
    T x1, y1, x2, y2;
};

template<class T>
T rectangleUnionArea(const std::vector<Rectangle<T>>& rect) {
    struct Event {
        T x, lo, hi;
        int delta;
    };
    std::vector<Event> ev;
    std::vector<T> y;
    for (auto [x1, y1, x2, y2] : rect) {
        if (x2 < x1) std::swap(x1, x2);
        if (y2 < y1) std::swap(y1, y2);
        if (x1 == x2 || y1 == y2) continue;
        ev.push_back({x1, y1, y2, 1});
        ev.push_back({x2, y1, y2, -1});
        y.push_back(y1);
        y.push_back(y2);
    }
    if (ev.empty()) return T{};

    std::sort(y.begin(), y.end());
    y.erase(std::unique(y.begin(), y.end()), y.end());
    std::sort(ev.begin(), ev.end(), [](const Event& a, const Event& b) {
        return a.x < b.x;
    });

    CoveredLength<T> cover(y);
    T ans{}, last = ev.front().x;
    for (std::size_t i = 0; i < ev.size(); ) {
        T x = ev[i].x;
        ans += (x - last) * cover.length();
        do {
            const auto& e = ev[i++];
            int l = static_cast<int>(std::lower_bound(y.begin(), y.end(), e.lo) -
                                     y.begin());
            int r = static_cast<int>(std::lower_bound(y.begin(), y.end(), e.hi) -
                                     y.begin());
            cover.modify(l, r, e.delta);
        } while (i < ev.size() && ev[i].x == x);
        last = x;
    }
    return ans;
}

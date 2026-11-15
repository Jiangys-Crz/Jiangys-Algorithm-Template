#include <algorithm>
#include <utility>
#include <vector>

#ifndef XCPC_GEOMETRY_COVERED_LENGTH_HPP
#define XCPC_GEOMETRY_COVERED_LENGTH_HPP

template<class T>
class CoveredLength {
public:
    explicit CoveredLength(std::vector<T> y)
        : y(std::move(y)), n(static_cast<int>(this->y.size()) - 1),
          cnt(4 * n), len(4 * n) {}

    void modify(int l, int r, int delta) {
        if (l < r) modify(1, 0, n, l, r, delta);
    }

    T length() const {
        return len[1];
    }

private:
    std::vector<T> y;
    int n;
    std::vector<int> cnt;
    std::vector<T> len;

    void pushup(int u, int l, int r) {
        if (cnt[u] > 0) len[u] = y[r] - y[l];
        else if (r - l == 1) len[u] = T{};
        else len[u] = len[u * 2] + len[u * 2 + 1];
    }

    void modify(int u, int l, int r, int ql, int qr, int delta) {
        if (ql <= l && r <= qr) {
            cnt[u] += delta;
            pushup(u, l, r);
            return;
        }

        int mid = l + (r - l) / 2;
        if (ql < mid) modify(u * 2, l, mid, ql, qr, delta);
        if (mid < qr) modify(u * 2 + 1, mid, r, ql, qr, delta);
        pushup(u, l, r);
    }
};

#endif

#ifndef XCPC_GEOMETRY_RECTANGLE_UNION_HPP
#define XCPC_GEOMETRY_RECTANGLE_UNION_HPP

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

#endif

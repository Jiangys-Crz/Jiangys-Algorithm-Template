#pragma once

#include <utility>
#include <vector>

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

#pragma once

#include <vector>

template<class Info>
struct SegmentTree {
    int base = 1;
    std::vector<Info> tr;

    explicit SegmentTree(const std::vector<Info>& a) {
        int n = static_cast<int>(a.size()) - 1;
        while (base < n) base *= 2;
        tr.resize(2 * base);
        for (int i = 1; i <= n; ++i) tr[base + i - 1] = a[i];
        for (int u = base - 1; u; --u) pushup(u);
    }

    void modify(int pos, const Info& val) {
        int u = base + pos - 1;
        tr[u] = val;
        for (u /= 2; u; u /= 2) pushup(u);
    }

    Info query(int l, int r) const {
        Info left{}, right{};
        for (l += base - 1, r += base; l < r; l /= 2, r /= 2) {
            if (l & 1) left = left + tr[l++];
            if (r & 1) right = tr[--r] + right;
        }
        return left + right;
    }

private:
    void pushup(int u) {
        tr[u] = tr[u * 2] + tr[u * 2 + 1];
    }
};

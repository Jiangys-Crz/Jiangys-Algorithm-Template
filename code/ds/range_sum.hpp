using ll = long long;

#ifndef XCPC_DS_LAZY_SEGMENT_TREE_HPP
#define XCPC_DS_LAZY_SEGMENT_TREE_HPP

template<class Info, class Tag>
struct LazySegmentTree {
    int n;
    vector<Info> tr;
    vector<Tag> tag;

    explicit LazySegmentTree(const vector<Info>& a)
        : n(a.empty() ? 0 : static_cast<int>(a.size()) - 1),
          tr(4ULL * n), tag(tr.size()) {
        if (n) build(1, 1, n, a);
    }

    void modify(int l, int r, const Tag& v) {
        if (l > r) return;
        assert(1 <= l && r <= n);
        modify(1, 1, n, l, r, v);
    }

    Info query(int l, int r) {
        if (l > r) return Info{};
        assert(1 <= l && r <= n);
        return query(1, 1, n, l, r);
    }

private:
    void pushup(int u) {
        tr[u] = tr[u * 2] + tr[u * 2 + 1];
    }

    void apply(int u, int len, const Tag& v) {
        tr[u].apply(v, len);
        tag[u].apply(v);
    }

    void pushdown(int u, int l, int r) {
        if (tag[u].isEmpty()) return;
        int mid = l + (r - l) / 2;
        apply(u * 2, mid - l + 1, tag[u]);
        apply(u * 2 + 1, r - mid, tag[u]);
        tag[u] = Tag{};
    }

    void build(int u, int l, int r, const vector<Info>& a) {
        if (l == r) {
            tr[u] = a[l];
            return;
        }
        int mid = l + (r - l) / 2;
        build(u * 2, l, mid, a);
        build(u * 2 + 1, mid + 1, r, a);
        pushup(u);
    }

    void modify(int u, int l, int r, int ql, int qr, const Tag& v) {
        if (ql <= l && r <= qr) {
            apply(u, r - l + 1, v);
            return;
        }
        pushdown(u, l, r);
        int mid = l + (r - l) / 2;
        if (ql <= mid) modify(u * 2, l, mid, ql, qr, v);
        if (qr > mid) modify(u * 2 + 1, mid + 1, r, ql, qr, v);
        pushup(u);
    }

    Info query(int u, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tr[u];
        pushdown(u, l, r);
        int mid = l + (r - l) / 2;
        if (qr <= mid) return query(u * 2, l, mid, ql, qr);
        if (ql > mid) return query(u * 2 + 1, mid + 1, r, ql, qr);
        return query(u * 2, l, mid, ql, qr) +
               query(u * 2 + 1, mid + 1, r, ql, qr);
    }
};

#endif

#ifndef XCPC_DS_RANGE_SUM_HPP
#define XCPC_DS_RANGE_SUM_HPP

struct RangeTag {
    bool hasSet = false;
    ll set = 0, add = 0;

    bool isEmpty() const {
        return !hasSet && add == 0;
    }

    // 将较新的操作追加到现有标记之后。
    void apply(const RangeTag& v) {
        if (v.hasSet) *this = v;
        else add += v.add;
    }
};

struct SumInfo {
    ll sum = 0;

    void apply(const RangeTag& v, int len) {
        if (v.hasSet) sum = v.set * len;
        sum += v.add * len;
    }

    friend SumInfo operator+(const SumInfo& a, const SumInfo& b) {
        return {a.sum + b.sum};
    }
};

#endif

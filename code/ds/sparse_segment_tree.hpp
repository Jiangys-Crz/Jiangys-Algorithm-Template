#include <optional>
#include <vector>

using ll = long long;
using ull = unsigned long long;

#ifndef XCPC_DS_SPARSE_SEGMENT_TREE_HPP
#define XCPC_DS_SPARSE_SEGMENT_TREE_HPP

class SparseSumTree {
public:
    SparseSumTree(ll lo, ll hi) : lo(lo), hi(hi) {}

    void modify(int& root, ll x, ll delta) {
        root = modify(root, lo, hi, x, delta);
    }

    ll query(int root, ll l, ll r) const {
        return query(root, lo, hi, l, r);
    }

    std::optional<ll> kth(int root, ll k) const {
        if (k <= 0 || k > tr[root].sum) return std::nullopt;
        ll l = lo, r = hi;
        while (l < r) {
            ll mid = midpoint(l, r);
            ll left = tr[tr[root].l].sum;
            if (k <= left) {
                root = tr[root].l;
                r = mid;
            } else {
                root = tr[root].r;
                l = mid + 1;
                k -= left;
            }
        }
        return l;
    }

    // Both roots must be independent trees in this pool.
    void merge(int& x, int& y) {
        x = merge(x, y, lo, hi);
        y = 0;
    }

private:
    struct Node {
        int l = 0, r = 0;
        ll sum = 0;
    };

    ll lo, hi;
    std::vector<Node> tr{Node{}};

    static ll midpoint(ll l, ll r) {
        return l + static_cast<ll>((ull(r) - ull(l)) / 2);
    }

    void pushup(int u) {
        tr[u].sum = tr[tr[u].l].sum + tr[tr[u].r].sum;
    }

    int modify(int u, ll l, ll r, ll x, ll delta) {
        if (!u) {
            u = static_cast<int>(tr.size());
            tr.emplace_back();
        }
        if (l == r) {
            tr[u].sum += delta;
            return u;
        }
        ll mid = midpoint(l, r);
        if (x <= mid) tr[u].l = modify(tr[u].l, l, mid, x, delta);
        else tr[u].r = modify(tr[u].r, mid + 1, r, x, delta);
        pushup(u);
        return u;
    }

    ll query(int u, ll l, ll r,
                    ll ql, ll qr) const {
        if (!u || r < ql || qr < l) return 0;
        if (ql <= l && r <= qr) return tr[u].sum;
        ll mid = midpoint(l, r);
        return query(tr[u].l, l, mid, ql, qr) +
               query(tr[u].r, mid + 1, r, ql, qr);
    }

    int merge(int x, int y, ll l, ll r) {
        if (!x || !y) return x ? x : y;
        if (l == r) {
            tr[x].sum += tr[y].sum;
            return x;
        }
        ll mid = midpoint(l, r);
        tr[x].l = merge(tr[x].l, tr[y].l, l, mid);
        tr[x].r = merge(tr[x].r, tr[y].r, mid + 1, r);
        pushup(x);
        return x;
    }
};

#endif

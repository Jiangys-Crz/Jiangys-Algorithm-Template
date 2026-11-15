#include "../types.hpp"
#include "../ds/fenwick.hpp"
#include "hld.hpp"

class RangeFenwick {
public:
    explicit RangeFenwick(int n) : b1(n), b2(n) {}

    void modify(int l, int r, ll val) {
        b1.add(l, val);
        b2.add(l, val * (l - 1));
        if (r < b1.n) {
            b1.add(r + 1, -val);
            b2.add(r + 1, -val * r);
        }
    }

    ll query(int l, int r) const {
        return prefix(r) - prefix(l - 1);
    }

private:
    Fenwick<ll> b1, b2;

    ll prefix(int i) const {
        return i * b1.query(i) - b2.query(i);
    }
};

struct TreePathSum {
    const HLD& tr;
    RangeFenwick bit;

    TreePathSum(const HLD& tr, const std::vector<ll>& a)
        : tr(tr), bit(tr.n) {
        for (int u = 1; u <= tr.n; ++u) {
            bit.modify(tr.dfn[u], tr.dfn[u], a[u]);
        }
    }

    void modify_path(int u, int v, ll val) {
        tr.for_path(u, v, [&](int l, int r) { bit.modify(l, r, val); });
    }

    ll query_path(int u, int v) const {
        ll res = 0;
        tr.for_path(u, v, [&](int l, int r) { res += bit.query(l, r); });
        return res;
    }

    void modify_tree(int u, ll val) {
        auto [l, r] = tr.subtree(u);
        bit.modify(l, r, val);
    }

    ll query_tree(int u) const {
        auto [l, r] = tr.subtree(u);
        return bit.query(l, r);
    }
};

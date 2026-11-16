using ll = long long;

#ifndef XCPC_DS_FHQ_TREAP_HPP
#define XCPC_DS_FHQ_TREAP_HPP

class FHQTreap {
public:
    void insert(ll val) {
        auto [x, y] = split(root, [&](ll a) { return a <= val; });
        tr.push_back({0, 0, 1, val, rnd()});
        root = merge(merge(x, static_cast<int>(tr.size()) - 1), y);
    }

    bool erase(ll val) {
        auto [x, yz] = split(root, [&](ll a) { return a < val; });
        auto [y, z] = split(yz, [&](ll a) { return a <= val; });
        bool removed = y != 0;
        if (removed) y = merge(tr[y].l, tr[y].r);
        root = merge(merge(x, y), z);
        return removed;
    }

    int get_rank(ll val) const {
        int ans = 1;
        for (int u = root; u; ) {
            int l = tr[u].l;
            if (val <= tr[u].val) {
                u = l;
            } else {
                ans += tr[l].siz + 1;
                u = tr[u].r;
            }
        }
        return ans;
    }

    optional<ll> get_val_by_rank(int k) const {
        if (k <= 0 || k > tr[root].siz) return nullopt;
        int u = root;
        while (true) {
            int left = tr[tr[u].l].siz;
            if (k == left + 1) return tr[u].val;
            if (k <= left) u = tr[u].l;
            else {
                k -= left + 1;
                u = tr[u].r;
            }
        }
    }

    optional<ll> get_prev(ll val) const {
        optional<ll> res;
        for (int u = root; u; ) {
            if (tr[u].val < val) {
                res = tr[u].val;
                u = tr[u].r;
            } else {
                u = tr[u].l;
            }
        }
        return res;
    }

    optional<ll> get_next(ll val) const {
        optional<ll> res;
        for (int u = root; u; ) {
            if (tr[u].val > val) {
                res = tr[u].val;
                u = tr[u].l;
            } else {
                u = tr[u].r;
            }
        }
        return res;
    }

private:
    struct Node {
        int l = 0, r = 0, siz = 0;
        ll val = 0;
        uint64_t key = 0;
    };

    vector<Node> tr{Node{}};
    int root = 0;
    mt19937_64 rnd{random_device{}()};

    void pushup(int u) {
        tr[u].siz = tr[tr[u].l].siz + tr[tr[u].r].siz + 1;
    }

    template<class F>
    pair<int, int> split(int u, const F& left) {
        if (!u) return {0, 0};
        if (left(tr[u].val)) {
            auto [x, y] = split(tr[u].r, left);
            tr[u].r = x;
            pushup(u);
            return {u, y};
        }
        auto [x, y] = split(tr[u].l, left);
        tr[u].l = y;
        pushup(u);
        return {x, u};
    }

    int merge(int x, int y) {
        if (!x || !y) return x ? x : y;
        if (tr[x].key < tr[y].key) {
            tr[x].r = merge(tr[x].r, y);
            pushup(x);
            return x;
        }
        tr[y].l = merge(x, tr[y].l);
        pushup(y);
        return y;
    }
};

#endif

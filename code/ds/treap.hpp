#pragma once

#include <array>
#include <cstdint>
#include <optional>
#include <random>
#include <vector>

#include "../types.hpp"

class Treap {
public:
    void insert(ll val) {
        root = insert(root, val);
    }

    bool erase(ll val) {
        bool removed = false;
        root = erase(root, val, removed);
        return removed;
    }

    int get_rank(ll val) const {
        int ans = 1;
        for (int u = root; u; ) {
            int l = tr[u].ch[0];
            if (val <= tr[u].val) {
                u = l;
            } else {
                ans += tr[l].siz + tr[u].cnt;
                u = tr[u].ch[1];
            }
        }
        return ans;
    }

    std::optional<ll> get_val_by_rank(int k) const {
        if (k <= 0 || k > tr[root].siz) return std::nullopt;
        int u = root;
        while (true) {
            int l = tr[u].ch[0], left = tr[l].siz;
            if (k <= left) u = l;
            else if (k <= left + tr[u].cnt) return tr[u].val;
            else {
                k -= left + tr[u].cnt;
                u = tr[u].ch[1];
            }
        }
    }

private:
    struct Node {
        std::array<int, 2> ch{};
        ll val = 0;
        std::uint64_t key = 0;
        int siz = 0, cnt = 0;
    };

    std::vector<Node> tr{Node{}};
    int root = 0;
    std::mt19937_64 rnd{std::random_device{}()};

    void pushup(int u) {
        auto [l, r] = tr[u].ch;
        tr[u].siz = tr[l].siz + tr[r].siz + tr[u].cnt;
    }

    int rotate(int u, int d) {
        int v = tr[u].ch[d];
        tr[u].ch[d] = tr[v].ch[d ^ 1];
        tr[v].ch[d ^ 1] = u;
        pushup(u);
        pushup(v);
        return v;
    }

    int insert(int u, ll val) {
        if (!u) {
            tr.push_back({{}, val, rnd(), 1, 1});
            return static_cast<int>(tr.size()) - 1;
        }
        if (val == tr[u].val) {
            ++tr[u].cnt;
        } else {
            int d = val > tr[u].val;
            int v = insert(tr[u].ch[d], val);
            tr[u].ch[d] = v;
            if (tr[v].key < tr[u].key) u = rotate(u, d);
        }
        pushup(u);
        return u;
    }

    int erase(int u, ll val, bool& removed) {
        if (!u) return 0;
        if (val != tr[u].val) {
            int d = val > tr[u].val;
            tr[u].ch[d] = erase(tr[u].ch[d], val, removed);
        } else if (tr[u].cnt > 1) {
            --tr[u].cnt;
            removed = true;
        } else {
            auto [l, r] = tr[u].ch;
            if (!l || !r) {
                removed = true;
                return l ? l : r;
            }
            int d = tr[l].key < tr[r].key ? 0 : 1;
            u = rotate(u, d);
            tr[u].ch[d ^ 1] = erase(tr[u].ch[d ^ 1], val, removed);
        }
        pushup(u);
        return u;
    }
};

#pragma once

#include "../types.hpp"
#include "tree.hpp"

struct TreePrefix {
    std::vector<int> fa;
    std::vector<ll> pre;

    TreePrefix(const Tree& tr, const std::vector<ll>& a)
        : fa(tr.fa), pre(tr.n + 1) {
        for (int i = 1; i <= tr.n; ++i) {
            int u = tr.id[i];
            pre[u] = pre[fa[u]] + a[u];
        }
    }

    ll nodeSum(int u, int v, int p) const {
        return (pre[u] - pre[p]) + (pre[v] - pre[fa[p]]);
    }

    ll edgeSum(int u, int v, int p) const {
        return (pre[u] - pre[p]) + (pre[v] - pre[p]);
    }
};

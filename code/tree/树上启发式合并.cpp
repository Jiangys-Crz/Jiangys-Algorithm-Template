#include "hld.hpp"

std::vector<int> countSubtreeColors(const HLD& tr, const std::vector<int>& color) {
    struct Task {
        int u;
        bool keep, collect;
    };

    std::vector<int> cnt(tr.n + 1), ans(tr.n + 1);
    int distinct = 0;
    auto change = [&](int u, int delta) {
        int& freq = cnt[color[u]];
        distinct -= freq > 0;
        freq += delta;
        distinct += freq > 0;
    };

    std::vector<Task> stk{{tr.root, true, false}};
    while (!stk.empty()) {
        auto [u, keep, collect] = stk.back();
        stk.pop_back();
        int h = tr.son[u];
        if (!collect) {
            stk.push_back({u, keep, true});
            if (h) stk.push_back({h, true, false});
            for (int v : tr.adj[u]) {
                if (tr.fa[v] == u && v != h) stk.push_back({v, false, false});
            }
            continue;
        }

        change(u, 1);
        auto [l, r] = tr.subtree(u);
        for (int i = l + 1 + tr.siz[h]; i <= r; ++i) change(tr.id[i], 1);
        ans[u] = distinct;
        if (!keep) {
            for (int i = l; i <= r; ++i) change(tr.id[i], -1);
        }
    }
    return ans;
}

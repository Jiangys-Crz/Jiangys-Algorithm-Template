#include <algorithm>
#include <utility>
#include <vector>

#ifndef XCPC_TREE_TREE_HPP
#define XCPC_TREE_TREE_HPP

struct Tree {
    int n, root = 0;
    vector<vector<int>> adj;
    vector<int> fa, dep, siz, dfn, id;

    explicit Tree(int n)
        : n(n), adj(n + 1), fa(n + 1), dep(n + 1),
          siz(n + 1), dfn(n + 1), id(n + 1) {}

    void add(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void work(int rt = 1) {
        root = rt;
        fa[root] = dep[root] = 0;
        vector<int> stk{root};
        int cnt = 0;
        while (!stk.empty()) {
            int u = stk.back();
            stk.pop_back();
            dfn[u] = ++cnt;
            id[cnt] = u;
            siz[u] = 1;
            for (auto it = adj[u].rbegin(); it != adj[u].rend(); ++it) {
                int v = *it;
                if (v == fa[u]) continue;
                fa[v] = u;
                dep[v] = dep[u] + 1;
                stk.push_back(v);
            }
        }
        for (int i = n; i >= 2; --i) {
            int u = id[i];
            siz[fa[u]] += siz[u];
        }
    }

    pair<int, int> subtree(int u) const {
        return {dfn[u], dfn[u] + siz[u] - 1};
    }

    bool isAncestor(int u, int v) const {
        auto [l, r] = subtree(u);
        return l <= dfn[v] && dfn[v] <= r;
    }
};

#endif

#ifndef XCPC_TREE_DIAMETER_HPP
#define XCPC_TREE_DIAMETER_HPP

struct Diameter {
    int u, v, len;
    vector<int> path;
};

inline Diameter treeDiameter(const Tree& tr) {
    vector<int> fa(tr.n + 1), q;
    auto farthest = [&](int root) {
        fa[root] = 0;
        q.assign(1, root);
        for (int i = 0; i < static_cast<int>(q.size()); ++i) {
            int u = q[i];
            for (int v : tr.adj[u]) {
                if (v == fa[u]) continue;
                fa[v] = u;
                q.push_back(v);
            }
        }
        return q.back();
    };

    int u = farthest(1);
    int v = farthest(u);
    vector<int> path;
    for (int x = v; x; x = fa[x]) path.push_back(x);
    reverse(path.begin(), path.end());
    int len = static_cast<int>(path.size()) - 1;
    return {u, v, len, move(path)};
}

#endif

vector<int> treeCenters(const Tree& tr) {
    auto [u, v, len, path] = treeDiameter(tr);
    if (len % 2 == 0) return {path[len / 2]};
    return {path[len / 2], path[len / 2 + 1]};
}

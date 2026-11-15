#include <algorithm>
#include <utility>
#include <vector>

#ifndef XCPC_TREE_TREE_HPP
#define XCPC_TREE_TREE_HPP

struct Tree {
    int n, root = 0;
    std::vector<std::vector<int>> adj;
    std::vector<int> fa, dep, siz, dfn, id;

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
        std::vector<int> stk{root};
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

    std::pair<int, int> subtree(int u) const {
        return {dfn[u], dfn[u] + siz[u] - 1};
    }

    bool isAncestor(int u, int v) const {
        auto [l, r] = subtree(u);
        return l <= dfn[v] && dfn[v] <= r;
    }
};

#endif

#ifndef XCPC_TREE_TREE_BFS_HPP
#define XCPC_TREE_TREE_BFS_HPP

struct TreeBfs {
    std::vector<int> order, fa, dep;

    explicit TreeBfs(const Tree& tr, int root = 1)
        : fa(tr.n + 1), dep(tr.n + 1) {
        order.push_back(root);
        for (int i = 0; i < static_cast<int>(order.size()); ++i) {
            int u = order[i];
            for (int v : tr.adj[u]) {
                if (v == fa[u]) continue;
                fa[v] = u;
                dep[v] = dep[u] + 1;
                order.push_back(v);
            }
        }
    }
};

#endif

#ifndef XCPC_TREE_DIAMETER_HPP
#define XCPC_TREE_DIAMETER_HPP

struct Diameter {
    int u, v, len;
    std::vector<int> path;
};

inline Diameter treeDiameter(const Tree& tr) {
    int u = TreeBfs(tr).order.back();
    TreeBfs bfs(tr, u);
    int v = bfs.order.back();

    std::vector<int> path;
    for (int x = v; x; x = bfs.fa[x]) path.push_back(x);
    std::reverse(path.begin(), path.end());
    return {u, v, bfs.dep[v], std::move(path)};
}

#endif

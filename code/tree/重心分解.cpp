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

struct CentroidDecomposition {
    std::vector<int> fa;

    explicit CentroidDecomposition(const Tree& tr) : fa(tr.n + 1) {
        std::vector<int> p(tr.n + 1), siz(tr.n + 1);
        std::vector<char> removed(tr.n + 1);
        std::vector<int> component;
        std::vector<std::pair<int, int>> stk{{1, 0}};
        while (!stk.empty()) {
            auto [start, parent] = stk.back();
            stk.pop_back();

            component.assign(1, start);
            p[start] = 0;
            for (int i = 0; i < static_cast<int>(component.size()); ++i) {
                int u = component[i];
                siz[u] = 1;
                for (int v : tr.adj[u]) {
                    if (removed[v] || v == p[u]) continue;
                    p[v] = u;
                    component.push_back(v);
                }
            }
            int total = static_cast<int>(component.size());
            for (int i = total - 1; i >= 1; --i) {
                int u = component[i];
                siz[p[u]] += siz[u];
            }

            int c = start;
            for (int u : component) {
                int largest = total - siz[u];
                for (int v : tr.adj[u]) {
                    if (!removed[v] && p[v] == u) {
                        largest = std::max(largest, siz[v]);
                    }
                }
                if (largest <= total / 2) {
                    c = u;
                    break;
                }
            }

            fa[c] = parent;
            removed[c] = true;
            for (int v : tr.adj[c]) {
                if (!removed[v]) stk.push_back({v, c});
            }
        }
    }
};

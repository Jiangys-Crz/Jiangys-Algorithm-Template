#include <algorithm>

#include "tree.hpp"

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

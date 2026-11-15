#include "graph.hpp"

struct FunctionalGraph {
    std::vector<int> bel, entry, dist, cycleLen;

    explicit FunctionalGraph(const std::vector<int>& next)
        : bel(next.size()), entry(next.size()), dist(next.size()), cycleLen{0} {
        int n = static_cast<int>(next.size()) - 1;
        std::vector<int> deg(n + 1), q;
        for (int u = 1; u <= n; ++u) ++deg[next[u]];
        for (int u = 1; u <= n; ++u) {
            if (!deg[u]) q.push_back(u);
        }
        for (std::size_t i = 0; i < q.size(); ++i) {
            int v = next[q[i]];
            if (--deg[v] == 0) q.push_back(v);
        }

        for (int u = 1; u <= n; ++u) {
            if (!deg[u] || bel[u]) continue;
            int id = static_cast<int>(cycleLen.size());
            int v = u, len = 0;
            do {
                bel[v] = id;
                entry[v] = v;
                ++len;
                v = next[v];
            } while (v != u);
            cycleLen.push_back(len);
        }
        for (std::size_t i = q.size(); i > 0; --i) {
            int u = q[i - 1], v = next[u];
            bel[u] = bel[v];
            entry[u] = entry[v];
            dist[u] = dist[v] + 1;
        }
    }
};

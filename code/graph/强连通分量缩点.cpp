#include "scc.hpp"

Graph condensation(const Graph& g, const SCC& scc) {
    Graph dag(scc.cnt);
    std::vector<std::vector<int>> nodes(scc.cnt + 1);
    std::vector<int> seen(scc.cnt + 1);
    for (int u = 1; u <= g.n; ++u) nodes[scc.bel[u]].push_back(u);

    for (int c = 1; c <= scc.cnt; ++c) {
        for (int u : nodes[c]) {
            for (auto [v, id] : g.adj[u]) {
                int d = scc.bel[v];
                if (c == d || seen[d] == c) continue;
                seen[d] = c;
                dag.addEdge(c, d);
            }
        }
    }
    return dag;
}

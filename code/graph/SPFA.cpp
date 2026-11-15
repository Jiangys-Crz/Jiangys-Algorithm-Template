#include <queue>

#include "bellman_ford.hpp"

RelaxResult spfa(const Graph& g, int s) {
    std::vector<lll> d(g.n + 1, graph_detail::wideInf);
    std::vector<int> len(g.n + 1);
    std::vector<char> inQueue(g.n + 1);
    std::queue<int> q;
    d[s] = 0;
    inQueue[s] = true;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inQueue[u] = false;
        for (auto [v, id] : g.adj[u]) {
            lll nd = d[u] + g.edges[id].w;
            if (nd >= d[v]) continue;
            d[v] = nd;
            len[v] = len[u] + 1;
            if (len[v] >= g.n) return graph_detail::finishRelaxation(d, true);
            if (!inQueue[v]) {
                inQueue[v] = true;
                q.push(v);
            }
        }
    }
    return graph_detail::finishRelaxation(d, false);
}

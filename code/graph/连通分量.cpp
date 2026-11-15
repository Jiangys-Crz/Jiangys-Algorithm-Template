#include "graph.hpp"

std::vector<int> connectedComponents(const Graph& g) {
    std::vector<int> bel(g.n + 1), stk;
    int cnt = 0;
    for (int s = 1; s <= g.n; ++s) {
        if (bel[s]) continue;
        bel[s] = ++cnt;
        stk.push_back(s);
        while (!stk.empty()) {
            int u = stk.back();
            stk.pop_back();
            for (auto [v, id] : g.adj[u]) {
                if (bel[v]) continue;
                bel[v] = cnt;
                stk.push_back(v);
            }
        }
    }
    return bel;
}

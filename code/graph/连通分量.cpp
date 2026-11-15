#include <cstddef>
#include <limits>
#include <vector>

using ll = long long;

#ifndef XCPC_GRAPH_GRAPH_HPP
#define XCPC_GRAPH_GRAPH_HPP

inline constexpr ll graphInf = std::numeric_limits<ll>::max() / 4;

struct Graph {
    struct Edge {
        int u, v;
        ll w;
    };
    struct Arc {
        int v, id;
    };

    int n;
    bool directed;
    std::vector<Edge> edges;
    std::vector<std::vector<Arc>> adj;

    explicit Graph(int n, bool directed = true)
        : n(n), directed(directed), adj(n + 1) {}

    int addEdge(int u, int v, ll w = 1) {
        int id = static_cast<int>(edges.size());
        edges.push_back({u, v, w});
        adj[u].push_back({v, id});
        if (!directed) adj[v].push_back({u, id});
        return id;
    }
};

#endif

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

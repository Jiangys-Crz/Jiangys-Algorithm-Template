#include <cstddef>
#include <functional>
#include <limits>
#include <optional>
#include <queue>
#include <tuple>
#include <vector>

using ll = long long;

#if defined(__SIZEOF_INT128__)
__extension__ using lll = __int128;
#endif

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

#ifndef XCPC_GRAPH_MST_RESULT_HPP
#define XCPC_GRAPH_MST_RESULT_HPP

struct MSTResult {
    ll weight = 0;
    std::vector<int> edges;
};

#endif

std::optional<MSTResult> prim(const Graph& g, int s = 1) {
    if (!g.n) return std::nullopt;
    using State = std::tuple<ll, int, int>;
    std::priority_queue<State, std::vector<State>, std::greater<>> pq;
    std::vector<char> vis(g.n + 1);
    MSTResult res;
    lll weight = 0;
    pq.push({0, -1, s});
    while (!pq.empty()) {
        auto [w, id, u] = pq.top();
        pq.pop();
        if (vis[u]) continue;
        vis[u] = true;
        if (id != -1) {
            weight += w;
            res.edges.push_back(id);
        }
        for (auto [v, e] : g.adj[u]) {
            if (!vis[v]) pq.push({g.edges[e].w, e, v});
        }
    }
    if (static_cast<int>(res.edges.size()) != g.n - 1) return std::nullopt;
    res.weight = static_cast<ll>(weight);
    return res;
}

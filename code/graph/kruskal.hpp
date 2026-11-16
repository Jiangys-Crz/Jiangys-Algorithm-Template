#include <algorithm>
#include <cstddef>
#include <limits>
#include <numeric>
#include <optional>
#include <utility>
#include <vector>

using ll = long long;

#if defined(__SIZEOF_INT128__)
__extension__ using lll = __int128;
#endif

#ifndef XCPC_GRAPH_GRAPH_HPP
#define XCPC_GRAPH_GRAPH_HPP

inline constexpr ll graphInf = numeric_limits<ll>::max() / 4;

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
    vector<Edge> edges;
    vector<vector<Arc>> adj;

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

#ifndef XCPC_GRAPH_GRAPH_DSU_HPP
#define XCPC_GRAPH_GRAPH_DSU_HPP

struct GraphDSU {
    vector<int> fa, siz;

    explicit GraphDSU(int n) : fa(n + 1), siz(n + 1, 1) {
        iota(fa.begin(), fa.end(), 0);
    }

    int find(int u) {
        while (u != fa[u]) {
            fa[u] = fa[fa[u]];
            u = fa[u];
        }
        return u;
    }

    bool merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        if (siz[u] < siz[v]) swap(u, v);
        fa[v] = u;
        siz[u] += siz[v];
        return true;
    }
};

#endif

#ifndef XCPC_GRAPH_MST_RESULT_HPP
#define XCPC_GRAPH_MST_RESULT_HPP

struct MSTResult {
    ll weight = 0;
    vector<int> edges;
};

#endif

#ifndef XCPC_GRAPH_KRUSKAL_HPP
#define XCPC_GRAPH_KRUSKAL_HPP

inline optional<MSTResult> kruskal(const Graph& g) {
    vector<int> ord(g.edges.size());
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int x, int y) {
        return g.edges[x].w < g.edges[y].w;
    });
    GraphDSU dsu(g.n);
    MSTResult res;
    lll weight = 0;
    for (int id : ord) {
        auto [u, v, w] = g.edges[id];
        if (!dsu.merge(u, v)) continue;
        weight += w;
        res.edges.push_back(id);
        if (static_cast<int>(res.edges.size()) == g.n - 1) break;
    }
    if (static_cast<int>(res.edges.size()) != g.n - 1) return nullopt;
    res.weight = static_cast<ll>(weight);
    return res;
}

#endif

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

#ifndef XCPC_GRAPH_BELLMAN_FORD_HPP
#define XCPC_GRAPH_BELLMAN_FORD_HPP

struct RelaxResult {
    vector<lll> dist;
    bool negativeCycle = false;
};

namespace graph_detail {
inline constexpr lll wideInf = lll{1} << 126;

}

inline RelaxResult bellmanFord(const Graph& g, int s) {
    vector<lll> d(g.n + 1, graph_detail::wideInf);
    d[s] = 0;
    auto relax = [&](int u, int v, ll w) {
        if (d[u] == graph_detail::wideInf || d[u] + w >= d[v]) return false;
        d[v] = d[u] + w;
        return true;
    };
    for (int i = 1; i <= g.n; ++i) {
        bool changed = false;
        for (auto [u, v, w] : g.edges) {
            changed |= relax(u, v, w);
            if (!g.directed) changed |= relax(v, u, w);
        }
        if (!changed) return {move(d), false};
    }
    return {move(d), true};
}

#endif

struct DifferenceConstraints {
    int n;
    Graph g;

    explicit DifferenceConstraints(int n) : n(n), g(n + 1) {
        for (int u = 1; u <= n; ++u) g.addEdge(n + 1, u, 0);
    }

    // 添加约束 x[u] - x[v] <= w。
    void add(int u, int v, ll w) {
        g.addEdge(v, u, w);
    }

    optional<vector<lll>> work() const {
        auto res = bellmanFord(g, n + 1);
        if (res.negativeCycle) return nullopt;
        res.dist.pop_back();
        return move(res.dist);
    }
};

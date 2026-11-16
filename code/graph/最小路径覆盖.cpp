using ll = long long;

#ifndef XCPC_GRAPH_BIPARTITE_MATCHING_HPP
#define XCPC_GRAPH_BIPARTITE_MATCHING_HPP

struct BipartiteMatching {
    int n, m;
    vector<vector<int>> adj;
    vector<int> match, vis;

    BipartiteMatching(int n, int m)
        : n(n), m(m), adj(n + 1), match(m + 1), vis(m + 1) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    int work() {
        fill(match.begin(), match.end(), 0);
        fill(vis.begin(), vis.end(), 0);
        int ans = 0;
        for (int u = 1; u <= n; ++u) ans += dfs(u, u);
        return ans;
    }

private:
    bool dfs(int u, int stamp) {
        for (int v : adj[u]) {
            if (vis[v] == stamp) continue;
            vis[v] = stamp;
            if (!match[v] || dfs(match[v], stamp)) {
                match[v] = u;
                return true;
            }
        }
        return false;
    }
};

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

#ifndef XCPC_GRAPH_TOPOSORT_HPP
#define XCPC_GRAPH_TOPOSORT_HPP

inline optional<vector<int>> topologicalSort(const Graph& g) {
    vector<int> deg(g.n + 1), order;
    for (auto [u, v, w] : g.edges) ++deg[v];
    for (int u = 1; u <= g.n; ++u) {
        if (!deg[u]) order.push_back(u);
    }
    for (size_t i = 0; i < order.size(); ++i) {
        int u = order[i];
        for (auto [v, id] : g.adj[u]) {
            if (--deg[v] == 0) order.push_back(v);
        }
    }
    if (static_cast<int>(order.size()) != g.n) return nullopt;
    return order;
}

#endif

optional<vector<vector<int>>> minimumPathCover(const Graph& g) {
    if (!topologicalSort(g)) return nullopt;

    BipartiteMatching bm(g.n, g.n);
    for (auto [u, v, w] : g.edges) bm.addEdge(u, v);
    bm.work();
    vector<int> next(g.n + 1);
    for (int v = 1; v <= g.n; ++v) {
        if (bm.match[v]) next[bm.match[v]] = v;
    }

    vector<vector<int>> paths;
    for (int u = 1; u <= g.n; ++u) {
        if (bm.match[u]) continue;
        auto& path = paths.emplace_back();
        for (int v = u; v; v = next[v]) path.push_back(v);
    }
    return paths;
}

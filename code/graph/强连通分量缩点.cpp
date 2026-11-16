using ll = long long;

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

#ifndef XCPC_GRAPH_SCC_HPP
#define XCPC_GRAPH_SCC_HPP

struct SCC {
    int cnt = 0;
    vector<int> dfn, low, bel;

    explicit SCC(const Graph& g)
        : dfn(g.n + 1), low(g.n + 1), bel(g.n + 1) {
        int timer = 0;
        vector<int> fa(g.n + 1), stk, call;
        vector<size_t> next(g.n + 1);
        auto enter = [&](int u) {
            dfn[u] = low[u] = ++timer;
            stk.push_back(u);
            call.push_back(u);
        };

        for (int s = 1; s <= g.n; ++s) {
            if (dfn[s]) continue;
            enter(s);
            while (!call.empty()) {
                int u = call.back();
                if (next[u] < g.adj[u].size()) {
                    int v = g.adj[u][next[u]++].v;
                    if (!dfn[v]) {
                        fa[v] = u;
                        enter(v);
                    } else if (!bel[v]) {
                        low[u] = min(low[u], dfn[v]);
                    }
                    continue;
                }
                call.pop_back();
                if (fa[u]) low[fa[u]] = min(low[fa[u]], low[u]);
                if (low[u] != dfn[u]) continue;

                ++cnt;
                int v;
                do {
                    v = stk.back();
                    stk.pop_back();
                    bel[v] = cnt;
                } while (v != u);
            }
        }
    }
};

#endif

Graph condensation(const Graph& g, const SCC& scc) {
    Graph dag(scc.cnt);
    vector<vector<int>> nodes(scc.cnt + 1);
    vector<int> seen(scc.cnt + 1);
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

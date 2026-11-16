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

#ifndef XCPC_GRAPH_DIJKSTRA_HPP
#define XCPC_GRAPH_DIJKSTRA_HPP

inline vector<ll> dijkstra(const Graph& g,
                                 const vector<int>& sources) {
    using State = pair<ll, int>;
    priority_queue<State, vector<State>, greater<>> pq;
    vector<ll> dist(g.n + 1, graphInf);
    for (int s : sources) {
        if (dist[s] == 0) continue;
        dist[s] = 0;
        pq.push({0, s});
    }
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        for (auto [v, id] : g.adj[u]) {
            ll w = g.edges[id].w;
            if (w >= graphInf - d) continue;
            ll nd = d + w;
            if (nd >= dist[v]) continue;
            dist[v] = nd;
            pq.push({nd, v});
        }
    }
    return dist;
}

inline vector<ll> dijkstra(const Graph& g, int s) {
    return dijkstra(g, vector<int>{s});
}

#endif

vector<int> countShortestPaths(const Graph& g, int s, int mod = 1000000007) {
    assert(mod > 0);
    auto dist = dijkstra(g, s);
    vector<int> ord(g.n), ways(g.n + 1);
    iota(ord.begin(), ord.end(), 1);
    sort(ord.begin(), ord.end(), [&](int u, int v) {
        return dist[u] < dist[v];
    });
    ways[s] = 1 % mod;
    for (int u : ord) {
        if (dist[u] == graphInf) break;
        for (auto [v, id] : g.adj[u]) {
            if (dist[v] != graphInf && g.edges[id].w == dist[v] - dist[u]) {
                ll sum = ll(ways[v]) + ways[u];
                ways[v] = static_cast<int>(sum >= mod ? sum - mod : sum);
            }
        }
    }
    return ways;
}

#include <algorithm>
#include <cstddef>
#include <limits>
#include <optional>
#include <vector>

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

struct TwoSAT {
    int n;
    Graph g;

    explicit TwoSAT(int n) : n(n), g(2 * n) {}

    static int lit(int x, bool value) {
        return 2 * x - !value;
    }

    static int neg(int p) {
        return p % 2 ? p + 1 : p - 1;
    }

    void addClause(int x, bool a, int y, bool b) {
        int p = lit(x, a), q = lit(y, b);
        g.addEdge(neg(p), q);
        g.addEdge(neg(q), p);
    }

    optional<vector<char>> work() const {
        SCC scc(g);
        vector<char> ans(n + 1);
        for (int x = 1; x <= n; ++x) {
            int p = lit(x, true), q = lit(x, false);
            if (scc.bel[p] == scc.bel[q]) return nullopt;
            ans[x] = scc.bel[p] < scc.bel[q];
        }
        return ans;
    }
};

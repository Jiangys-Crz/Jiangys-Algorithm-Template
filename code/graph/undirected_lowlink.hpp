#include <algorithm>
#include <cstddef>
#include <limits>
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

#ifndef XCPC_GRAPH_UNDIRECTED_LOWLINK_HPP
#define XCPC_GRAPH_UNDIRECTED_LOWLINK_HPP

struct UndirectedLowlink {
    vector<int> dfn, low;
    vector<char> cut, bridge;
    vector<vector<int>> blocks;

    explicit UndirectedLowlink(const Graph& g)
        : dfn(g.n + 1), low(g.n + 1), cut(g.n + 1), bridge(g.edges.size()) {
        int timer = 0;
        vector<int> fa(g.n + 1), pe(g.n + 1, -1), children(g.n + 1);
        vector<int> call, stk, seen(g.n + 1, -1);
        vector<size_t> next(g.n + 1);
        auto popBlock = [&](int last) {
            int mark = static_cast<int>(blocks.size()), id;
            auto& block = blocks.emplace_back();
            do {
                id = stk.back();
                stk.pop_back();
                auto [u, v, w] = g.edges[id];
                for (int x : {u, v}) {
                    if (seen[x] == mark) continue;
                    seen[x] = mark;
                    block.push_back(x);
                }
            } while (id != last);
        };

        for (int s = 1; s <= g.n; ++s) {
            if (dfn[s]) continue;
            dfn[s] = low[s] = ++timer;
            call.push_back(s);
            if (g.adj[s].empty()) blocks.push_back({s});
            while (!call.empty()) {
                int u = call.back();
                if (next[u] < g.adj[u].size()) {
                    auto [v, id] = g.adj[u][next[u]++];
                    if (id == pe[u]) continue;
                    if (!dfn[v]) {
                        fa[v] = u;
                        pe[v] = id;
                        ++children[u];
                        dfn[v] = low[v] = ++timer;
                        stk.push_back(id);
                        call.push_back(v);
                    } else if (dfn[v] < dfn[u]) {
                        low[u] = min(low[u], dfn[v]);
                        stk.push_back(id);
                    }
                    continue;
                }
                call.pop_back();
                int p = fa[u];
                if (!p) {
                    cut[u] = children[u] > 1;
                    continue;
                }
                low[p] = min(low[p], low[u]);
                if (low[u] > dfn[p]) bridge[pe[u]] = true;
                if (low[u] >= dfn[p]) {
                    if (fa[p]) cut[p] = true;
                    popBlock(pe[u]);
                }
            }
        }
    }
};

#endif

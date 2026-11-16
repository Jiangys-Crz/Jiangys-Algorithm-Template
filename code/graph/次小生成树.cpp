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

#ifndef XCPC_GRAPH_PATH_MAX_HPP
#define XCPC_GRAPH_PATH_MAX_HPP

struct MaxTwo {
    optional<ll> first, second;

    void add(ll w) {
        if (!first || w > *first) {
            second = first;
            first = w;
        } else if (w < *first && (!second || w > *second)) {
            second = w;
        }
    }

    void merge(const MaxTwo& other) {
        if (other.first) add(*other.first);
        if (other.second) add(*other.second);
    }
};

struct TreePathMax {
    vector<int> dep;
    vector<vector<int>> up;
    vector<vector<MaxTwo>> mx;

    explicit TreePathMax(const Graph& tr, int root = 1) : dep(tr.n + 1) {
        int lg = 1;
        while ((1LL << lg) <= tr.n) ++lg;
        up.assign(lg, vector<int>(tr.n + 1));
        mx.assign(lg, vector<MaxTwo>(tr.n + 1));
        vector<int> order{root};
        for (size_t i = 0; i < order.size(); ++i) {
            int u = order[i];
            for (auto [v, id] : tr.adj[u]) {
                if (v == up[0][u]) continue;
                up[0][v] = u;
                mx[0][v].add(tr.edges[id].w);
                dep[v] = dep[u] + 1;
                order.push_back(v);
            }
        }
        for (int j = 1; j < lg; ++j) {
            for (int u = 1; u <= tr.n; ++u) {
                int p = up[j - 1][u];
                up[j][u] = up[j - 1][p];
                mx[j][u] = mx[j - 1][u];
                mx[j][u].merge(mx[j - 1][p]);
            }
        }
    }

    MaxTwo query(int u, int v) const {
        MaxTwo res;
        if (dep[u] < dep[v]) swap(u, v);
        int delta = dep[u] - dep[v];
        for (int j = 0; delta; ++j, delta >>= 1) {
            if (!(delta & 1)) continue;
            res.merge(mx[j][u]);
            u = up[j][u];
        }
        if (u == v) return res;
        for (int j = static_cast<int>(up.size()) - 1; j >= 0; --j) {
            if (up[j][u] == up[j][v]) continue;
            res.merge(mx[j][u]);
            res.merge(mx[j][v]);
            u = up[j][u];
            v = up[j][v];
        }
        res.merge(mx[0][u]);
        res.merge(mx[0][v]);
        return res;
    }
};

#endif

optional<ll> strictSecondMST(const Graph& g) {
    auto mst = kruskal(g);
    if (!mst) return nullopt;

    Graph tr(g.n, false);
    vector<char> used(g.edges.size());
    for (int id : mst->edges) {
        auto [u, v, w] = g.edges[id];
        tr.addEdge(u, v, w);
        used[id] = true;
    }

    TreePathMax path(tr);
    optional<lll> ans;
    for (size_t id = 0; id < g.edges.size(); ++id) {
        auto [u, v, w] = g.edges[id];
        if (used[id] || u == v) continue;
        auto [first, second] = path.query(u, v);
        auto removed = first && w == *first ? second : first;
        if (!removed) continue;
        lll weight = lll(mst->weight) + w - *removed;
        if (!ans || weight < *ans) ans = weight;
    }
    if (!ans) return nullopt;
    return static_cast<ll>(*ans);
}

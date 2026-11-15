#include <cstddef>
#include <limits>
#include <optional>
#include <utility>
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

#ifndef XCPC_GRAPH_PATH_MAX_HPP
#define XCPC_GRAPH_PATH_MAX_HPP

struct MaxTwo {
    std::optional<ll> first, second;

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
    std::vector<int> dep;
    std::vector<std::vector<int>> up;
    std::vector<std::vector<MaxTwo>> mx;

    explicit TreePathMax(const Graph& tr, int root = 1) : dep(tr.n + 1) {
        int lg = 1;
        while ((1LL << lg) <= tr.n) ++lg;
        up.assign(lg, std::vector<int>(tr.n + 1));
        mx.assign(lg, std::vector<MaxTwo>(tr.n + 1));
        std::vector<int> order{root};
        for (std::size_t i = 0; i < order.size(); ++i) {
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
        if (dep[u] < dep[v]) std::swap(u, v);
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

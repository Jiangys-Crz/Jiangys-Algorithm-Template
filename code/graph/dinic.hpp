#include <algorithm>
#include <limits>
#include <vector>

using ll = long long;

#ifndef XCPC_GRAPH_DINIC_HPP
#define XCPC_GRAPH_DINIC_HPP

template<class T = ll>
struct Flow {
    struct Edge {
        int v;
        T cap;
    };

    std::vector<Edge> e;
    std::vector<std::vector<int>> adj;

    explicit Flow(int n) : adj(n + 1), cur(n + 1), h(n + 1) {}

    int addEdge(int u, int v, T cap) {
        int id = static_cast<int>(e.size());
        adj[u].push_back(id);
        adj[v].push_back(id + 1);
        e.push_back({v, cap});
        e.push_back({u, 0});
        return id;
    }

    T maxFlow(int s, int t) {
        if (s == t) return 0;
        T ans = 0;
        while (true) {
            bfs(s);
            if (h[t] == -1) return ans;
            std::fill(cur.begin(), cur.end(), 0);
            while (T pushed = dfs(s, t, std::numeric_limits<T>::max())) {
                ans += pushed;
            }
        }
    }

    std::vector<char> cutSide(int s) {
        bfs(s);
        std::vector<char> side(h.size());
        for (std::size_t u = 1; u < h.size(); ++u) side[u] = h[u] != -1;
        return side;
    }

private:
    std::vector<std::size_t> cur;
    std::vector<int> h;

    void bfs(int s) {
        std::fill(h.begin(), h.end(), -1);
        h[s] = 0;
        std::vector<int> q{s};
        for (std::size_t i = 0; i < q.size(); ++i) {
            int u = q[i];
            for (int id : adj[u]) {
                auto [v, cap] = e[id];
                if (cap <= 0 || h[v] != -1) continue;
                h[v] = h[u] + 1;
                q.push_back(v);
            }
        }
    }

    T dfs(int u, int t, T f) {
        if (u == t) return f;
        for (auto& i = cur[u]; i < adj[u].size(); ++i) {
            int id = adj[u][i];
            auto [v, cap] = e[id];
            if (cap <= 0 || h[v] != h[u] + 1) continue;
            T pushed = dfs(v, t, std::min(f, cap));
            if (!pushed) continue;
            e[id].cap -= pushed;
            e[id ^ 1].cap += pushed;
            return pushed;
        }
        return 0;
    }
};

#endif

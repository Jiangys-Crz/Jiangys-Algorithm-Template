#include <algorithm>
#include <functional>
#include <optional>
#include <queue>
#include <utility>

#include "graph.hpp"

struct MinCostFlow {
    struct Edge {
        int v;
        ll cap;
        lll cost;
    };

    int n;
    std::vector<Edge> e;
    std::vector<std::vector<int>> adj;

    explicit MinCostFlow(int n) : n(n), adj(n + 1) {}

    int addEdge(int u, int v, ll cap, ll cost) {
        int id = static_cast<int>(e.size());
        adj[u].push_back(id);
        adj[v].push_back(id + 1);
        e.push_back({v, cap, cost});
        e.push_back({u, 0, -lll(cost)});
        return id;
    }

    std::optional<std::pair<ll, ll>> work(
        int s, int t, ll limit = std::numeric_limits<ll>::max()) {
        ll flow = 0;
        lll cost = 0;
        if (s == t || limit == 0) return std::pair{0LL, 0LL};

        constexpr lll inf = lll{1} << 126;
        std::vector<lll> pi(n + 1), dist(n + 1);
        std::vector<int> pre(n + 1);
        if (!initPotential(pi)) return std::nullopt;

        using State = std::pair<lll, int>;
        while (flow < limit) {
            std::fill(dist.begin(), dist.end(), inf);
            std::priority_queue<State, std::vector<State>, std::greater<>> pq;
            dist[s] = 0;
            pq.push({0, s});
            while (!pq.empty()) {
                auto [d, u] = pq.top();
                pq.pop();
                if (d != dist[u]) continue;
                for (int id : adj[u]) {
                    auto [v, cap, w] = e[id];
                    if (cap <= 0) continue;
                    lll nd = d + w + pi[u] - pi[v];
                    if (nd >= dist[v]) continue;
                    dist[v] = nd;
                    pre[v] = id;
                    pq.push({nd, v});
                }
            }
            if (dist[t] == inf) break;
            for (int u = 1; u <= n; ++u) {
                if (dist[u] != inf) pi[u] += dist[u];
            }

            ll pushed = limit - flow;
            for (int u = t; u != s; u = e[pre[u] ^ 1].v) {
                pushed = std::min(pushed, e[pre[u]].cap);
            }
            for (int u = t; u != s; u = e[pre[u] ^ 1].v) {
                int id = pre[u];
                e[id].cap -= pushed;
                e[id ^ 1].cap += pushed;
            }
            flow += pushed;
            cost += pushed * (pi[t] - pi[s]);
        }
        return std::pair{flow, static_cast<ll>(cost)};
    }

private:
    bool initPotential(std::vector<lll>& pi) const {
        for (int k = 1; k <= n; ++k) {
            bool changed = false;
            for (int u = 1; u <= n; ++u) {
                for (int id : adj[u]) {
                    auto [v, cap, w] = e[id];
                    if (cap <= 0 || pi[u] + w >= pi[v]) continue;
                    pi[v] = pi[u] + w;
                    changed = true;
                }
            }
            if (!changed) return true;
        }
        return false;
    }
};

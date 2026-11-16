using ll = long long;

#if defined(__SIZEOF_INT128__)
__extension__ using lll = __int128;
#endif

struct MinCostFlow {
    struct Edge {
        int v;
        ll cap;
        lll cost;
    };

    int n;
    vector<Edge> e;
    vector<vector<int>> adj;

    explicit MinCostFlow(int n) : n(n), adj(n + 1) {}

    int addEdge(int u, int v, ll cap, ll cost) {
        int id = static_cast<int>(e.size());
        adj[u].push_back(id);
        adj[v].push_back(id + 1);
        e.push_back({v, cap, cost});
        e.push_back({u, 0, -lll(cost)});
        return id;
    }

    optional<pair<ll, ll>> work(
        int s, int t, ll limit = numeric_limits<ll>::max()) {
        ll flow = 0;
        lll cost = 0;
        if (s == t || limit == 0) return pair{0LL, 0LL};

        constexpr lll inf = lll{1} << 126;
        vector<lll> pi(n + 1), dist(n + 1);
        vector<int> pre(n + 1);
        if (!initPotential(pi)) return nullopt;

        using State = pair<lll, int>;
        while (flow < limit) {
            fill(dist.begin(), dist.end(), inf);
            priority_queue<State, vector<State>, greater<>> pq;
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
                pushed = min(pushed, e[pre[u]].cap);
            }
            lll delta, nextCost;
            if (__builtin_mul_overflow(lll(pushed), pi[t] - pi[s], &delta) ||
                __builtin_add_overflow(cost, delta, &nextCost)) {
                return nullopt;
            }
            for (int u = t; u != s; u = e[pre[u] ^ 1].v) {
                int id = pre[u];
                e[id].cap -= pushed;
                e[id ^ 1].cap += pushed;
            }
            flow += pushed;
            cost = nextCost;
        }
        if (cost < numeric_limits<ll>::min() ||
            cost > numeric_limits<ll>::max()) return nullopt;
        return pair{flow, static_cast<ll>(cost)};
    }

private:
    bool initPotential(vector<lll>& pi) const {
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

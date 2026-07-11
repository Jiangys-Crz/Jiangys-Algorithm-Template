template<class T>
struct Flow {
	int n;
	std::vector<std::pair<int, T>> e;
	std::vector<std::vector<int>> g;
	std::vector<int> cur, h;

	Flow(int _) {
		init(_);
	}

	void init(int _) {
		n = _ + 1;
		g.resize(n);
	}

	bool bfs(int s, int t) {
		h.assign(n, -1);
		std::queue<int> q;
		h[s] = 0;
		q.push(s);
		while (q.size()) {
			const int u = q.front();
			q.pop();
			for (int i : g[u]) {
				auto [v, c] = e[i];
				if (h[v] == -1 && c > 0) {
					h[v] = h[u] + 1;
					if (v == t) {
						return true;
					}
					q.push(v);
				}
			}
		}
		return false;
	}

	T dfs(int u, int t, T f) {
		if (u == t) {
			return f;
		}
		auto r = f;
		for (int &i = cur[u]; i < g[u].size(); i++) {
			const int j = g[u][i];
			auto [v, c] = e[j];
			if (h[v] == h[u] + 1 && c > 0) {
				auto a = dfs(v, t, std::min(r, c));
				e[j].second -= a;
				e[j ^ 1].second += a;
				r -= a;
				if (r == 0) {
					return f;
				}
			}
		}
		return f - r;
	}

	void addEdge(int u, int v, T c) {
		g[u].push_back(e.size());
		e.emplace_back(v, c);
		g[v].push_back(e.size());
		e.emplace_back(u, 0);
	}

	T maxFlow(int s, int t) {
		T ans = 0;
		while (bfs(s, t)) {
			cur.assign(n, 0);
			ans += dfs(s, t, std::numeric_limits<T>::max());
		}
		return ans;
	}

};
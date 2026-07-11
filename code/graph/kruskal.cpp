struct Kruskal {
	int n, m;
	struct Edges {
		int a, b, c;

		bool operator< (const Edges& W) const {
			return c < W.c;
		}
	};

	std::vector<Edges> edges;

	Kruskal() {}
	Kruskal(int n, int m): n(n), m(m) {}

	void addEdge(int u, int v, int w) {
		edges.emplace_back(u, v, w);
	}

	int work() {
		DSU dsu(n);
		int ans = 0, res = 0;
		sort(edges.begin(), edges.end());
		for (int i = 0; i < m; i++) {
			int a = edges[i].a, b = edges[i].b, c = edges[i].c;
			if (!dsu.same(a, b)) {
				ans += c;
				res++;
				dsu.merge(a, b);
			}
		}

		return (res < n - 1 ? -1 : ans);
	}
};
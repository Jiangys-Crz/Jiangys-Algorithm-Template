const u64 mask = std::mt19937_64(time(nullptr))();

u64 shift(u64 x) {
	x ^= mask;
  	x ^= x << 13;
  	x ^= x >> 7;
  	x ^= x << 17;
  	x ^= mask;
  	return x;
}

struct HashTree {
	int n;
	std::vector<std::vector<int>> e;
	std::vector<u64> f;

	HashTree() {}
	HashTree(int n) {
		init(n + 1);
	} 

	void init(int n) {
		this->n = n;
		e.resize(n);
		f.assign(n, 0);
	}

	void addEdge(int u, int v) {
		e[u].push_back(v);
	}

	void dfs(int u, int fa) {
		f[u] = 1;
		for (auto v : e[u]) {
			if (v == fa) {
				continue;
			}
			dfs(v, u);
			f[u] += shift(f[v]);
		}
	}

	u64 getHash(int root = 1) {
		dfs(root, 0);
		return f[root];
	}
};
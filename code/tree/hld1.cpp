template<class T>
struct HLD {
	int n;
	std::vector<std::vector<int>> adj;
	std::vector<int> siz, dep; 
	std::vector<int> top, son, fa, dfn, id;
	int cnt;

	HLD(int n_) {
		n = n_;
		cnt = 0;
		adj.resize(n + 1);
		siz.resize(n + 1);
		dep.resize(n + 1);
		top.resize(n + 1);
		son.resize(n + 1);
		fa.resize(n + 1);
		dfn.resize(n + 1);
		id.resize(n + 1);
	}

	void add(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	std::function<void(int)> dfs1 = [&](int x) -> void {
		siz[x] = 1;
		dep[x] = dep[fa[x]] + 1;
		for (auto y : adj[x]) {
			if (y == fa[x]) continue;
			fa[y] = x;
			dfs1(y);
			siz[x] += siz[y];
			if (siz[y] > siz[son[x]]) {
				son[x] = y;
			}
		}
	};
	std::function<void(int,int)> dfs2 = [&](int x, int t) -> void {
		top[x] = t;
		dfn[x] = ++ cnt;
		id[cnt] = x;
		if (son[x]) {
			dfs2(son[x], t);
		}
		for (auto y : adj[x]) {
			if (y == fa[x] || y == son[x]) continue;
			dfs2(y, y);
		}
	};

	int lca(int x, int y) {
		while (top[x] != top[y]) {
			if (dep[top[x]] > dep[top[y]]) {
				x = fa[top[x]];
			} else {
				y = fa[top[y]];
			}
		}
		return dep[x] < dep[y] ? x : y;
	}
    // 树链路径
	int calc(int x, int y) {
		return dep[x] + dep[y] - 2 * dep[lca(x, y)];
	}
    
	void work(int root = 1) {
		dfs1(root);
		dfs2(root, root);
	}

    /* 以下是线段树维护 路径、子树 和 */
	void modify_path(int u, int v, int k, auto& seg) {
		while (top[u] != top[v]) {
			if (dep[top[u]] < dep[top[v]]) {
				std::swap(u, v);
			};
			seg.modify(dfn[top[u]], dfn[u], Tag {k});
			u = fa[top[u]];
		}
		if (dep[u] < dep[v]) {
			std::swap(u, v);
		}
		seg.modify(dfn[v], dfn[u], Tag {k});
	}

	T query_path(int u, int v, auto& seg) {
		T ans = 0;
		while (top[u] != top[v]) {
			if (dep[top[u]] < dep[top[v]]) {
				std::swap(u, v);
			}
			ans += seg.query(dfn[top[u]], dfn[u]).sum;
			u = fa[top[u]];
		}
		if (dep[u] < dep[v]) {
			std::swap(u, v);
		}
		ans += seg.query(dfn[v], dfn[u]).sum;
		return ans;
	}

	void modify_tree(int u, int k, auto& seg) {
		seg.modify(dfn[u], dfn[u] + siz[u] - 1, Tag {k});
	}

	T query_tree(int u, auto& seg) {
		return seg.query(dfn[u], dfn[u] + siz[u] - 1).sum;
	}

};
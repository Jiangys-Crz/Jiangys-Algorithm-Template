struct LCT {
	struct Node {
		int s[2], p;
		int rev;
		int v, sum;
	};
	std::vector<Node> tr;
	std::vector<int> stk;
	int n;

	LCT(int _n) : n(_n + 1) {
		init(n);
	}

	void init(int n) {
		tr.assign(n, {});
		stk.assign(n, 0);
	}

	void pushup(int u) {
		tr[u].sum = tr[tr[u].s[0]].sum ^ tr[u].v ^ tr[tr[u].s[1]].sum;
	}

	void pushrev(int u) {
		std::swap(tr[u].s[0], tr[u].s[1]);
		tr[u].rev ^= 1;
	}

	void pushdown(int u) {
		if (tr[u].rev) {
			pushrev(tr[u].s[0]);
			pushrev(tr[u].s[1]);
			tr[u].rev = 0;
		}
	}

	bool isroot(int u) {
		return tr[tr[u].p].s[0] != u && tr[tr[u].p].s[1] != u;
	}

	void rotate(int u) {
		int y = tr[u].p, z = tr[y].p;
		int k = tr[y].s[1] == u;
		if (!isroot(y)) {
			tr[z].s[tr[z].s[1] == y] = u;
		}
		tr[u].p = z;
		tr[y].s[k] = tr[u].s[k ^ 1];
		tr[tr[u].s[k ^ 1]].p = y;
		tr[u].s[k ^ 1] = y;
		tr[y].p = u;
		pushup(y), pushup(u);
	}

	void splay(int u) {
		int top = 0, x = u;
		stk[++ top] = x;
		while (!isroot(x)) {
			stk[++ top] = x = tr[x].p;
		}
		while (top) {
			pushdown(stk[top --]);
		}
		while (!isroot(u)) {
			int y = tr[u].p, z = tr[y].p;
			if (!isroot(y)) {
				if ((tr[z].s[1] == y) ^ (tr[y].s[1] == u)) {
					rotate(u);
				} else {
					rotate(y);
				}
			}
			rotate(u);
		}
	}

	void access(int u) {
		int z = u;
		for (int y = 0; u; y = u, u = tr[u].p) {
			splay(u);
			tr[u].s[1] = y;
			pushup(u);
		}
		splay(z);
	}

	void makeroot(int u) {
		access(u);
		pushrev(u);
	}

	int findroot(int u) {
		access(u);
		while (tr[u].s[0]) {
			pushdown(u);
			u = tr[u].s[0];
		}
		splay(u);
		return u;
	}

	void split(int x, int y) {
		makeroot(x);
		access(y);
	}

	void link(int x, int y) {
		makeroot(x);
		if (findroot(y) != x) {
			tr[x].p = y;
		}
	}

	void cut(int x, int y) {
		makeroot(x);
		if (findroot(y) == x && tr[x].s[1] == y && !tr[y].s[0]) {
			tr[y].p = tr[x].s[1] = 0;
			pushup(x);
		}
	}
};
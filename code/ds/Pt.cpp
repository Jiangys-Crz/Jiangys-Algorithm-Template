template<class Info>
struct PresidentTree {
	int idx = 0, n;
	std::vector<int> root;
	std::vector<Info> tr;

	PresidentTree() {}
	PresidentTree(int _, int m) : n(m), root(_ + 1), tr(_ << 5) {}

	void init(int _, int m) {
		n = m;
		root.resize(_ + 1);
		tr.resize(_ << 5);
	}

	void pushup(int u) {
		int l = tr[u].l, r = tr[u].r;
		tr[u] = tr[l] + tr[r];
		tr[u].l = l;
		tr[u].r = r;
	}

	// 插入
	void modify(int &u, int v, int l, int r, int pos, int x) {
		tr[u = ++ idx] = tr[v];
		if (l == r) {
			tr[u].sum += x;
			return;
		}
		int mid = l + r >> 1;
		if (pos <= mid) {
			modify(tr[u].l, tr[v].l, l, mid, pos, x);
		} else {
			modify(tr[u].r, tr[v].r, mid + 1, r, pos, x);
		}
		pushup(u);
	}

	void modify(int &u, int v, int pos, int x) {
		modify(u, v, 1, n, pos, x);
	}

	Info query(int u, int v, int l, int r, int x, int y) {
		if (x > r || y < l || x > y) {
			return Info();
		}
		if (x <= l && y >= r) {
			return tr[v] - tr[u];
		}
		int mid = (l + r) / 2;
		return query(tr[u].l, tr[v].l, l, mid, x, y) + 
		query(tr[u].r, tr[v].r, mid + 1, r, x, y);
	}

	Info query(int u, int v, int l, int r) {
		return query(u, v, 1, n, l, r);
	}
};

struct Info {
	int l, r;
	i64 sum;
};

Info operator+ (const Info &a, const Info &b) {
	Info res;
	res.sum = a.sum + b.sum;
	return res;
}

Info operator- (const Info &a, const Info &b) {
	Info res;
	res.sum = a.sum - b.sum;
	return res;
}
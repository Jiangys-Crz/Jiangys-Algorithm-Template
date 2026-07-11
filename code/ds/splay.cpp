constexpr int INF = (1 << 31) + 1;

struct SplayTree {
	struct node {
		int s[2];
		int p, v, cnt, siz;
		void init(int _p, int _v) {
			p = _p;
			v = _v;
			cnt = siz = 1;
		}
	};
	int root = 0, idx = 0;
	std::vector<node> tr;
	SplayTree (int _n) {
		tr.assign(_n + 1, {});
	}
	
	void pushup(int x) {
		tr[x].siz = tr[tr[x].s[0]].siz + tr[tr[x].s[1]].siz + tr[x].cnt;
	}
	
	void rotate(int x) {
		int y = tr[x].p, z = tr[y].p;
		int k = tr[y].s[1] == x;
		tr[y].s[k] = tr[x].s[k ^ 1];
		tr[tr[x].s[k ^ 1]].p = y;
		tr[x].s[k ^ 1] = y;
		tr[y].p = x;
		tr[z].s[tr[z].s[1] == y] = x;
		tr[x].p = z;
		pushup(y), pushup(x);
	}
	
	void splay(int x, int k) {
		while (tr[x].p != k) {
			int y = tr[x].p, z = tr[y].p;
			if (z != k) {
				(tr[y].s[0] == x) ^ (tr[z].s[0] == y) ? rotate(x) : rotate(y);
			}
			rotate(x);
		}
		if (k == 0) root = x;
	}
	
	void insert(int v) {
		int x = root, p = 0;
		while (x && tr[x].v != v) {
			p = x;
			x = tr[x].s[v > tr[x].v];
		}
		if (x) tr[x].cnt++;
		else {
			x = ++idx;
			tr[p].s[v > tr[p].v] = x;
			tr[x].init(p, v);
		}
		splay(x, 0);
	}
	
	void find(int v) {
		int x = root;
		while (tr[x].s[v > tr[x].v] && v != tr[x].v) {
			x = tr[x].s[v > tr[x].v];
		}
		splay(x, 0);
	}
	
	int get_pre(int v) {
		find(v);
		int x = root;
		if (tr[x].v < v) return x;
		x = tr[x].s[0];
		while (tr[x].s[1]) x = tr[x].s[1];
		splay(x, 0);
		return x;
	}
	
	int get_suc(int v) {
		find(v);
		int x = root;
		if (tr[x].v > v) return x;
		x = tr[x].s[1];
		while (tr[x].s[0]) x = tr[x].s[0];
		splay(x, 0);
		return x;
	}
	
	void del(int v) {
		int pre = get_pre(v);
		int suc = get_suc(v);
		splay(pre, 0), splay(suc, pre);
		int del = tr[suc].s[0];
		if (tr[del].cnt > 1) {
			tr[del].cnt--, splay(del, 0);
		} else {
			tr[suc].s[0] = 0, splay(suc, 0);
		}
	}
	
	int get_rank(int v) {
		insert(v);
		int res = tr[tr[root].s[0]].siz;
		del(v);
		return res;
	}
	
	int get_val(int k) {
		int x = root;
		while (true) {
			int y = tr[x].s[0];
			if (tr[y].siz + tr[x].cnt < k) {
				k -= tr[y].siz + tr[x].cnt;
				x = tr[x].s[1];
			} else if (tr[y].siz >= k) {
				x = y;
			} else {
				break;
			}
		}
		splay(x, 0);
		return tr[x].v;
	}
};
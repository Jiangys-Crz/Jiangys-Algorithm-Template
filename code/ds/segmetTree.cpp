constexpr int INF = 1e9;

#define ls u << 1
#define rs u << 1 | 1

template<class Info, class Tag>
struct SegmentTree {
	int n;
	std::vector<Info> tr;
	std::vector<Tag> tag;
	SegmentTree(int _): n(_), tr(_ << 2), tag(_ << 2) {}
	SegmentTree(std::vector<int> a): SegmentTree(int(a.size() - 1)) {
		std::function<void(int, int, int)> build = [&](int u, int l, int r) -> void {
			if (l == r) {
				tr[u] = {l, r, a[l], a[l]};
				return;
			}
			tr[u] = {l, r};
			int mid = (l + r) >> 1;
			build(ls, l, mid), build(rs, mid + 1, r);
			pushup(u);
		};

		build(1, 1, n);
	}

	void apply(int u, const Tag& v) {
		tr[u].apply(v);
		tag[u].apply(v);
	}

	void pushdown(int u) {
		if (tag[u].isEmpty()) return;
		apply(ls, tag[u]);
		apply(rs, tag[u]);
		tag[u] = Tag();
	}

	void pushup(int u) {
		tr[u] = tr[ls] + tr[rs];
	}

	void modify(int u, int l, int r, const Tag& v) {
		if (l <= tr[u].l && r >= tr[u].r) {
			apply(u, v);
			return;
		}
		pushdown(u);
		int mid = (tr[u].l + tr[u].r) >> 1;
		if (l <= mid) {
			modify(ls, l, r, v);
		} 
		if (r > mid) {
			modify(rs, l, r, v);
		}
		pushup(u);
	}

	void modify(int l, int r, const Tag& v) {
		modify(1, l, r, v);
	}

	Info query(int u, int l, int r) {
		if (l <= tr[u].l && tr[u].r <= r) {
			return tr[u];
		}
        pushdown(u);
		if (r <= tr[ls].r) {
			return query(ls, l, r);
		} else if (l >= tr[rs].l) {
			return query(rs, l, r);
		} else {
			return query(ls, l, r) + query(rs, l, r);
		}
	}

	Info query(int l, int r) {
		return Info(1, l, r);
	}

	template<class F>
    int findFirst(int u, int l, int r, F &&pred) {
        if (tr[u].l > r || tr[u].r < l || !pred(tr[u])) {
            return -1;
        }
        if (tr[u].l == tr[u].r) {
            return tr[u].l;
        }
        int res = findFirst(ls, l, r, pred);
        if (res == -1) {
            res = findFirst(rs, l, r, pred);
        }
        return res;
    }

    template<class F>
    int findFirst(int l, int r, F &&pred) {
        return findFirst(1, l, r, pred);
    }

    template<class F>
    int findLast(int u, int l, int r, F &&pred) {
        if (tr[u].l > r || tr[u].r < l || !pred(tr[u])) {
            return -1;
        }
        if (tr[u].l == tr[u].r) {
            return tr[u].l;
        }
        int res = findLast(rs, l, r, pred);
        if (res == -1) {
            res = findLast(ls, l, r, pred);
        }
        return res;
    }

    template<class F>
    int findLast(int l, int r, F &&pred) {
        return findLast(1, l, r, pred);
    }
};

struct Tag {
	ll val;
    Tag(): val(0){}
    Tag(ll _val): val(_val) {}
	void apply(Tag t) {
		val = t.val;
	}
	bool isEmpty() {
		return val == 0;
	}
};

struct Info {
	int l, r;
	ll max, min;
	void apply(Tag v) {
		max = v.val;
        min = v.val;
	}
};

Info operator+(Info a, Info b){
    Info res;
    res.l = a.l;
    res.r = b.r;
    res.max = std::max(a.max, b.max);
    res.min = std::min(a.min, b.min);
    return res;
}
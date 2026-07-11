template<class T, typename F>
struct RMQ {
	const int n, k;
	std::vector<std::vector<T>> f;
	RMQ(int _) : n(_), k(std::log2(_)) {
		f.resize(k + 1, std::vector<T>(n + 1));
	}

	RMQ(std::vector<F> in) : RMQ(int(in.size())) {
		for (int i = 1; i < n; i++) {
			f[0][i].apply(in[i]);
		}
		for (int i = 0, t = 1; i < k; i++, t <<= 1) {
			const int P = n - (t << 1) + 1;
			for (int j = 1; j <= P; j++) {
				f[i + 1][j] = f[i][j] + f[i][j + t];
			}
		}
	}

	T query(int l, int r) {
		if (l > r) {
			std::swap(l, r);
		}
		int k = std::log2(r - l + 1);
		return f[k][l] + f[k][r - (1 << k) + 1];
	}
};

struct Info {
	i64 max, min;
	void apply(i64 v) {
		max = min = v;
	}
};

Info operator+ (const Info &a, const Info &b) {
	Info res;
	res.max = std::max(a.max, b.max);
	res.min = std::min(a.min, b.min);
	return res;
}
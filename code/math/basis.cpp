struct Basis {
	int cnt;

	std::vector<ll> b, p;

	Basis() {
		b.resize(64);
		p.resize(64);
		cnt = 0;
	}

	bool insert(ll x) {
		for (int i = 63; i >= 0; i--) {
			if (x & (1ull << i)) {
				if (!b[i]) {
					b[i] = x;
					return true;
				}
				x ^= b[i];
			}
		}
		return false;
	}

	void build() {
		for(int i = 63; i >= 0; i--) {
            for(int j = i - 1; j >= 0; j--) {
                if(b[i] & (1ull << j)) {
                    b[i] ^= b[j];
                }
            }
		}
		cnt = 0;
        for(int i = 0; i <= 60; i++) {
            if(b[i]) {
            	p[cnt++] = b[i];
            }
        }
	}

	ll kth(ll x) {
		ll res = 0;
		if (x >= (1ull << cnt)) {
			return -1;
		}
        build();
		for (int i = 63; i >= 0; i--) {
			if (x & (1ull << i)) {
				res ^= p[i];
			}
		}
		return res;
	}
};
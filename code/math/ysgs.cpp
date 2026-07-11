constexpr int N = 1E6;

std::vector<i64> d, primes, num;
std::vector<bool> st;

void init(int n) {
    d.resize(n + 1);
    num.resize(n + 1);
    st.assign(n + 1, false);
    primes.clear();

	d[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!st[i]) {
			primes.push_back(i);
			d[i] = 2;
            num[i] = 1;
		}
		for (auto p : primes) {
			if (p * i > n) {
				break;
			}
			st[i * p] = true;
			if (i % p == 0) {
				d[i * p] = d[i] / (num[i] + 1) * (num[i] + 2);
                num[i * p] = num[i] + 1;
				break;
			}
			d[i * p] = d[i] * 2;
            num[i * p] = 1;
		}
	}
}
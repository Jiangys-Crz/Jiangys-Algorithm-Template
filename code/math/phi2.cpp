constexpr int N = 1E6;

std::vector<i64> phi, primes;
std::vector<bool> st;

void init(int n) {
    phi.resize(n);
    st.assign(n + 1, false);
    primes.clear();

	phi[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!st[i]) {
			primes.push_back(i);
			phi[i] = i - 1;
		}
		for (auto p : primes) {
			if (p * i > n) {
				break;
			}
			st[i * p] = true;
			if (i % p == 0) {
				phi[i * p] = phi[i] * p;
				break;
			}
			phi[i * p] = phi[i] * (p - 1);
		}
	}
}
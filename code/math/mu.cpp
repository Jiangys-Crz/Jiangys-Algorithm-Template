constexpr int N = 1E7;

std::vector<int> mu, primes;
std::vector<bool> st;

void init(int n) {
	mu.resize(n + 1);
	primes.clear();
	st.assign(n + 1, false);

	mu[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!st[i]) {
			mu[i] = -1;
			primes.push_back(i);
		}

		for (auto p : primes) {
			if (i * p > n) {
				break;
			}
			st[i * p] = true;
			if (i % p == 0) {
				mu[i * p] = 0;
				break;
			}
			mu[i * p] = -mu[i];
		}
	}
	for (int i = 1; i <= n; i++) {
		mu[i] += mu[i - 1];
	}
}
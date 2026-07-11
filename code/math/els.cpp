constexpr int N = 1E6;

std::vector<i64> primes;
std::vector<bool> st;

void init(int n) {
    st.assign(n + 1, false);
    primes.clear();

    st[0] = st[1] = true;
	for (int i = 2; i <= n; i++) {
		if (!st[i]) {
			primes.push_back(i);
		}
		for (auto p : primes) {
			if (p * i > n) {
				break;
			}
			st[i * p] = true;
			if (i % p == 0) {
				break;
			}
		}
	}
}
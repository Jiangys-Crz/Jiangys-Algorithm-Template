constexpr int N = 1E6;

std::vector<i64> sd, primes, num;
std::vector<bool> st;

void init(int n) {
    sd.resize(n + 1);
    num.resize(n + 1);
    st.assign(n + 1, false);
    primes.clear();

	sd[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!st[i]) {
			primes.push_back(i);
			sd[i] = num[i] = i + 1;
		}
		for (auto p : primes) {
			if (p * i > n) {
				break;
			}
			st[i * p] = true;
			if (i % p == 0) {
				sd[i * p] = sd[i] / num[i] * (num[i] * p + 1);
                num[i * p] = num[i] * p + 1;
				break;
			}
			sd[i * p] = sd[i] * sd[p];
            num[i * p] = p + 1;
		}
	}
}
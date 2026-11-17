constexpr int N = 1E7;

std::vector<ll> primes, mu, phi;
std::vector<bool> st;
std::map<ll, ll> mp_mu, mp_phi;

void init(int n) {
	primes.clear();
	mu.resize(n + 1);
	phi.resize(n + 1);
	st.assign(n + 1, false);
	mu[1] = phi[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!st[i]) {
			primes.push_back(i);
			mu[i] = -1;
			phi[i] = i - 1;
		}
		for (auto p : primes) {
			if (p * i > n) break;
			st[i * p] = true;
			if (i % p == 0) {
				mu[i * p] = 0;
				phi[i * p] = phi[i] * p;
				break;
			}
			mu[i * p] = -mu[i];
			phi[i * p] = phi[i] * (p - 1);
		}
	}
	for (int i = 1; i <= n; i++) {
		mu[i] += mu[i - 1];
		phi[i] += phi[i - 1];
	}
}

ll Sphi(ll n) {
	if (n < N) return phi[n];
	if (mp_phi[n]) return mp_phi[n];
	ll ans = (n + 1) * n / 2;
	for (ll l = 2, r; l <= n; l = r + 1) {
		r = n / (n / l);
		ans -= Sphi(n / l) * (r - l + 1);
	}
	mp_phi[n] = ans;
	return mp_phi[n];
}

ll Smu(ll n) {
	if (n < N) return mu[n];
	if (mp_mu[n]) return mp_mu[n];
	ll ans = 1;
	for (ll l = 2, r; l <= n; l = r + 1) {
		r = n / (n / l);
		ans -= Smu(n / l) * (r - l + 1);
	}
	mp_mu[n] = ans;
	return mp_mu[n];
}
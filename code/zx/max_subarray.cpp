#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

ll solve(const vector<ll>& a) {
    ll ans = a.front();
#ifdef BRUTE
    for (size_t l = 0; l < a.size(); ++l) {
        ll sum = 0;
        for (size_t r = l; r < a.size(); ++r) {
            sum += a[r];
            ans = max(ans, sum);
        }
    }
#else
    ll pre = 0, low = 0;
    for (ll x : a) {
        pre += x;
        ans = max(ans, pre - low);
        low = min(low, pre);
    }
#endif
    return ans;
}

int main() {
    int n;
    if (!(cin >> n) || n <= 0) return 1;
    vector<ll> a(n);
    for (ll& x : a) {
        if (!(cin >> x)) return 1;
    }
    cout << solve(a) << '\n';
}

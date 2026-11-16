using ll = long long;
using ull = unsigned long long;

// In solve: ll l, r are the inclusive search bounds, l <= r.
// The initial r must be feasible.
auto check = [&](ll x) -> bool {
    // Return true exactly when x satisfies the problem constraints.
    // If x is feasible, every candidate >= x must be feasible.
    return /* TODO: feasibility of x */;
};

while (l < r) {
    ull width = ull(r) - ull(l);
    ll mid = l + static_cast<ll>(width / 2);
    if (check(mid)) r = mid;
    else l = mid + 1;
}
ll ans = l;

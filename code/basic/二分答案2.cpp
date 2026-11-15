#include "../types.hpp"

template<class Check>
ll maxFeasible(ll l, ll r, Check check) {
    while (l < r) {
        ull width = ull(r) - ull(l);
        ll mid = r - static_cast<ll>(width / 2);
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    return l;
}

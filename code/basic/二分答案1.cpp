#include "../types.hpp"

template<class Check>
ll minFeasible(ll l, ll r, Check check) {
    while (l < r) {
        ull width = ull(r) - ull(l);
        ll mid = l + static_cast<ll>(width / 2);
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    return l;
}

#include <algorithm>
#include <vector>

using ll = long long;

// In solve: vector<ll> a. tails.size() is the LIS length.

std::vector<ll> tails;
for (ll x : a) {
    auto it = std::lower_bound(tails.begin(), tails.end(), x);
    if (it == tails.end()) tails.push_back(x);
    else *it = x;
}

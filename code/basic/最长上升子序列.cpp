#include <algorithm>
#include <vector>

using ll = long long;

// 先准备数组 a。tails.size() 为最长上升子序列的长度。

vector<ll> tails;
for (ll x : a) {
    auto it = lower_bound(tails.begin(), tails.end(), x);
    if (it == tails.end()) tails.push_back(x);
    else *it = x;
}

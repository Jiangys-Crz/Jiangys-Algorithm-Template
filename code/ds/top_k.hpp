#include <functional>
#include <optional>
#include <queue>
#include <vector>

using ll = long long;

#if defined(__SIZEOF_INT128__)
__extension__ using lll = __int128;
#endif

#ifndef XCPC_DS_TOP_K_HPP
#define XCPC_DS_TOP_K_HPP

template<class Better>
class TopK {
public:
    explicit TopK(int k, Better better = Better{})
        : k(k), better(better), q(better) {}

    void insert(ll x) {
        if (!k) return;
        if (static_cast<int>(q.size()) < k) {
            q.push(x);
            sum += x;
        } else if (better(x, q.top())) {
            ll removed = q.top();
            q.pop();
            q.push(x);
            sum = static_cast<ll>(lll(sum) - removed + x);
        }
    }

    ll total() const {
        return sum;
    }

    optional<ll> kth() const {
        if (!k || static_cast<int>(q.size()) < k) return nullopt;
        return q.top();
    }

private:
    int k;
    ll sum = 0;
    Better better;
    priority_queue<ll, vector<ll>, Better> q;
};

using KLargest = TopK<greater<ll>>;
using KSmallest = TopK<less<ll>>;

#endif

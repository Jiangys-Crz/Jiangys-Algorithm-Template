#include <functional>
#include <optional>
#include <queue>
#include <utility>
#include <vector>

using ll = long long;

struct MedianHeap {
    priority_queue<ll> lo;
    priority_queue<ll, vector<ll>, greater<>> hi;

    void insert(ll x) {
        if (lo.empty() || x <= lo.top()) lo.push(x);
        else hi.push(x);

        if (lo.size() < hi.size()) {
            lo.push(hi.top());
            hi.pop();
        } else if (lo.size() > hi.size() + 1) {
            hi.push(lo.top());
            lo.pop();
        }
    }

    optional<pair<ll, ll>> middle() const {
        if (lo.empty()) return nullopt;
        ll left = lo.top();
        return pair{left, lo.size() == hi.size() ? hi.top() : left};
    }
};

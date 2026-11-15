#include <functional>
#include <optional>
#include <queue>
#include <utility>
#include <vector>

#include "../types.hpp"

struct MedianHeap {
    std::priority_queue<ll> lo;
    std::priority_queue<ll, std::vector<ll>, std::greater<>> hi;

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

    std::optional<std::pair<ll, ll>> middle() const {
        if (lo.empty()) return std::nullopt;
        ll left = lo.top();
        return std::pair{left, lo.size() == hi.size() ? hi.top() : left};
    }
};

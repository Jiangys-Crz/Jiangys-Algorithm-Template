#include <iterator>
#include <optional>
#include <set>

using ll = long long;

struct OrderedMultiset {
    std::multiset<ll> s;

    void insert(ll x) {
        s.insert(x);
    }

    bool erase(ll x) {
        auto it = s.find(x);
        if (it == s.end()) return false;
        s.erase(it);
        return true;
    }

    std::optional<ll> get_prev(ll x) const {
        auto it = s.lower_bound(x);
        if (it == s.begin()) return std::nullopt;
        return *std::prev(it);
    }

    std::optional<ll> get_next(ll x) const {
        auto it = s.upper_bound(x);
        if (it == s.end()) return std::nullopt;
        return *it;
    }
};

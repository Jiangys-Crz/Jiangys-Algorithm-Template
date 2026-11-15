#pragma once

#include <cstddef>
#include <functional>
#include <optional>
#include <utility>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#include "../types.hpp"

template<class Key>
using OrderedTree = __gnu_pbds::tree<
    Key, __gnu_pbds::null_type, std::less<Key>, __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update>;

class OrderMultiset {
public:
    void insert(ll x) {
        tr.insert({x, ++idx});
    }

    bool erase(ll x) {
        auto it = tr.lower_bound({x, 0});
        if (it == tr.end() || it->first != x) return false;
        tr.erase(it);
        return true;
    }

    std::size_t countLess(ll x) const {
        return tr.order_of_key({x, 0});
    }

    std::optional<ll> kth(std::size_t k) const {
        auto it = tr.find_by_order(k);
        if (it == tr.end()) return std::nullopt;
        return it->first;
    }

private:
    OrderedTree<std::pair<ll, ull>> tr;
    ull idx = 0;
};

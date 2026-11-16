#include <cstddef>
#include <functional>
#include <optional>
#include <utility>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using ll = long long;
using ull = unsigned long long;

#ifndef XCPC_STL_PBDS_ORDERED_TREE_HPP
#define XCPC_STL_PBDS_ORDERED_TREE_HPP

template<class Key>
using OrderedTree = __gnu_pbds::tree<
    Key, __gnu_pbds::null_type, less<Key>, __gnu_pbds::rb_tree_tag,
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

    size_t countLess(ll x) const {
        return tr.order_of_key({x, 0});
    }

    optional<ll> kth(size_t k) const {
        auto it = tr.find_by_order(k);
        if (it == tr.end()) return nullopt;
        return it->first;
    }

private:
    OrderedTree<pair<ll, ull>> tr;
    ull idx = 0;
};

#endif

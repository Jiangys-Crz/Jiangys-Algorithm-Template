#include <algorithm>
#include <tuple>
#include <vector>

using ll = long long;

#ifndef XCPC_STL_RECORD_SORT_HPP
#define XCPC_STL_RECORD_SORT_HPP

struct Record {
    int id;
    ll score, penalty;
};

inline void sortRecords(std::vector<Record>& a) {
    std::sort(a.begin(), a.end(), [](const Record& x, const Record& y) {
        if (x.score != y.score) return x.score > y.score;
        return std::tie(x.penalty, x.id) < std::tie(y.penalty, y.id);
    });
}

#endif

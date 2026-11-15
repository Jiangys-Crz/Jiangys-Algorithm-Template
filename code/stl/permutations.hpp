#pragma once

#include <algorithm>
#include <utility>
#include <vector>

template<class T, class F>
void forEachPermutation(std::vector<T> a, F visit, bool descending = false) {
    std::sort(a.begin(), a.end());
    if (descending) std::reverse(a.begin(), a.end());

    do {
        visit(std::as_const(a));
    } while (descending ? std::prev_permutation(a.begin(), a.end())
                        : std::next_permutation(a.begin(), a.end()));
}

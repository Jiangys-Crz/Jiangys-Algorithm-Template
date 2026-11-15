#include <vector>

template<class T>
int lastAtMost(const std::vector<T>& a, const T& x) {
    int l = 0, r = static_cast<int>(a.size()) - 1;
    while (l < r) {
        int mid = r - (r - l) / 2;
        if (a[mid] <= x) l = mid;
        else r = mid - 1;
    }
    return l;
}

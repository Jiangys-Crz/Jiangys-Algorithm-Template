#include <vector>

template<class T>
int firstAtLeast(const std::vector<T>& a, const T& x) {
    int l = 1, r = static_cast<int>(a.size());
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (a[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return l;
}

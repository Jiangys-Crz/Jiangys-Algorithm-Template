#include <algorithm>
#include <limits>
#include <utility>
#include <vector>

int maxDisjointIntervals(std::vector<std::pair<int, int>> intervals) {
    std::sort(intervals.begin(), intervals.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    int count = 0;
    int lastEnd = std::numeric_limits<int>::min();
    for (auto [left, right] : intervals) {
        if (left >= lastEnd) {
            ++count;
            lastEnd = right;
        }
    }
    return count;
}

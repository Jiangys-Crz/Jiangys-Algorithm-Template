#include <cstddef>
#include <string>
#include <vector>

int countGridPaths(const std::vector<std::string>& grid) {
    if (grid.empty() || grid.front().empty()) return 0;
    constexpr int mod = 1000000007;
    const auto columns = grid.front().size();
    std::vector<int> ways(columns);
    ways[0] = 1;

    for (const auto& row : grid) {
        for (std::size_t col = 0; col < columns; ++col) {
            if (row[col] == '#') {
                ways[col] = 0;
            } else if (col > 0) {
                ways[col] += ways[col - 1];
                if (ways[col] >= mod) ways[col] -= mod;
            }
        }
    }
    return ways.back();
}

#include <cstddef>
#include <string>
#include <vector>

// In solve: nonempty rectangular grid; an empty grid has answer 0.
// A path may move right or down.

// Positive modulus chosen for the problem.
const int mod = /* TODO: modulus */;
std::size_t columns = grid.front().size();
std::vector<int> ways(columns);
ways[0] = 1 % mod;

for (const auto& row : grid) {
    for (std::size_t col = 0; col < columns; ++col) {
        if (/* TODO: this cell is blocked */) {
            ways[col] = 0;
        } else if (col > 0) {
            ways[col] = (1LL * ways[col] + ways[col - 1]) % mod;
        }
    }
}
int ans = ways.back();

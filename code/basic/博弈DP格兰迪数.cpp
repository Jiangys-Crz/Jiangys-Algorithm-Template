#include <vector>

// In solve: int n is the maximum heap size; moves contains positive legal takes.

std::vector<int> grundy(n + 1);
std::vector<int> seen(moves.size() + 1, -1);
for (int stones = 1; stones <= n; ++stones) {
    for (int take : moves) {
        if (take <= stones) seen[grundy[stones - take]] = stones;
    }
    int value = 0;
    while (seen[value] == stones) ++value;
    grundy[stones] = value;
}

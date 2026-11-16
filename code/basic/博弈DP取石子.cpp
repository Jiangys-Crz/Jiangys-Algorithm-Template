#include <vector>

// In solve: int n is the maximum heap size; moves contains positive legal takes.

std::vector<char> win(n + 1);
for (int stones = 1; stones <= n; ++stones) {
    for (int take : moves) {
        if (take <= stones && !win[stones - take]) {
            win[stones] = true;
            break;
        }
    }
}

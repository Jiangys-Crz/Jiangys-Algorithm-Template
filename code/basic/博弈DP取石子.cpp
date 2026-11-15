#include <vector>

bool canWinStones(int n, const std::vector<int>& moves) {
    std::vector<char> win(n + 1);
    for (int stones = 1; stones <= n; ++stones) {
        for (int take : moves) {
            if (take <= stones && !win[stones - take]) {
                win[stones] = true;
                break;
            }
        }
    }
    return win[n];
}

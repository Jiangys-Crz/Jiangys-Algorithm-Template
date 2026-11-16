#include <iostream>
#include <vector>

int main() {
    int n, m;
    if (!(std::cin >> n >> m)) return 0;
    std::vector<int> moves(m);
    for (int& x : moves) std::cin >> x;

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
    for (int x : grundy) std::cout << x << ' ';
    std::cout << '\n';
}

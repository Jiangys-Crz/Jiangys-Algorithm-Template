#include <iostream>
#include <vector>

int main() {
    int n, m;
    if (!(std::cin >> n >> m)) return 0;
    std::vector<int> moves(m);
    for (int& x : moves) std::cin >> x;

    std::vector<char> win(n + 1);
    for (int stones = 1; stones <= n; ++stones) {
        for (int take : moves) {
            if (take <= stones && !win[stones - take]) {
                win[stones] = true;
                break;
            }
        }
    }
    std::cout << (win[n] ? "First" : "Second") << '\n';
}

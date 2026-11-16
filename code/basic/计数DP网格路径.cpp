#include <iostream>
#include <cstddef>
#include <string>
#include <vector>

int main() {
    std::size_t rows, columns;
    if (!(std::cin >> rows >> columns)) return 0;
    if (rows == 0 || columns == 0) {
        std::cout << "0\n";
        return 0;
    }
    constexpr int mod = 1000000007;
    std::vector<int> ways(columns);
    ways[0] = 1;

    for (std::size_t i = 0; i < rows; ++i) {
        std::string row;
        std::cin >> row;
        for (std::size_t col = 0; col < columns; ++col) {
            if (row[col] == '#') {
                ways[col] = 0;
            } else if (col > 0) {
                ways[col] += ways[col - 1];
                if (ways[col] >= mod) ways[col] -= mod;
            }
        }
    }
    std::cout << ways.back() << '\n';
}

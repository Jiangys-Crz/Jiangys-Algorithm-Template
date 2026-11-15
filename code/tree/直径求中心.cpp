#include "diameter.hpp"

std::vector<int> treeCenters(const Tree& tr) {
    auto [u, v, len, path] = treeDiameter(tr);
    if (len % 2 == 0) return {path[len / 2]};
    return {path[len / 2], path[len / 2 + 1]};
}

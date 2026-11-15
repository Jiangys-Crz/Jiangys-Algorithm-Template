#include <cstdint>

// visit receives every submask, including the empty submask.
template <class Visit>
void forEachSubmask(std::uint64_t mask, Visit visit) {
    std::uint64_t subset = mask;
    while (true) {
        visit(subset);
        if (subset == 0) {
            break;
        }
        subset = (subset - 1) & mask;
    }
}

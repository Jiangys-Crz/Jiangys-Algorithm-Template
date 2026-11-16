#include <algorithm>

// In solve: int n is the sequence length.
// TODO: Initialize the state of the empty window.
auto add = [&](int i) {
    // TODO: Add element i to the window state.
};
auto remove = [&](int i) {
    // TODO: Remove element i from the window state.
};
auto valid = [&]() -> bool {
    // Return true exactly when the current window is feasible.
    // Every subwindow of a feasible window must also be feasible.
    return /* TODO: feasibility of the current window */;
};

int l = 0, ans = 0;
for (int r = 0; r < n; ++r) {
    add(r);
    while (l <= r && !valid()) remove(l++);
    ans = std::max(ans, r - l + 1);
}

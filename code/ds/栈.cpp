#include <stack>
#include <string_view>

bool isBalanced(std::string_view s) {
    std::stack<char> stk;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            stk.push(c);
            continue;
        }
        if (stk.empty()) return false;
        char left = stk.top();
        if ((left == '(' && c != ')') ||
            (left == '[' && c != ']') ||
            (left == '{' && c != '}')) return false;
        stk.pop();
    }
    return stk.empty();
}

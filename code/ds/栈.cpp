#include <stack>
#include <string>

// In solve: s contains only parentheses, square brackets or braces.

std::stack<char> stk;
bool matched = true;
for (char c : s) {
    if (c == '(' || c == '[' || c == '{') {
        stk.push(c);
        continue;
    }
    if (stk.empty()) {
        matched = false;
        break;
    }
    char left = stk.top();
    if ((left == '(' && c != ')') ||
        (left == '[' && c != ']') ||
        (left == '{' && c != '}')) {
        matched = false;
        break;
    }
    stk.pop();
}
matched = matched && stk.empty();

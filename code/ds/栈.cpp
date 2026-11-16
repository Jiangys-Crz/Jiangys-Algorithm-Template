#include <iostream>
#include <stack>
#include <string>

int main() {
    std::string s;
    if (!std::getline(std::cin, s)) return 0;
    std::stack<char> stk;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            stk.push(c);
            continue;
        }
        if (stk.empty()) {
            std::cout << "NO\n";
            return 0;
        }
        char left = stk.top();
        if ((left == '(' && c != ')') ||
            (left == '[' && c != ']') ||
            (left == '{' && c != '}')) {
            std::cout << "NO\n";
            return 0;
        }
        stk.pop();
    }
    std::cout << (stk.empty() ? "YES" : "NO") << '\n';
}

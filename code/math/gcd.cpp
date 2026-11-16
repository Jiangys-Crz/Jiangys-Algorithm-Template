using ull = unsigned long long;

// a 和 b 为无符号整数。循环结束后，a 为最大公约数。

while (b) {
    ull r = a % b;
    a = b;
    b = r;
}

std::ostream &operator<<(std::ostream &os, i128 n) {
    if (n == 0) return os << "0";
    if (n < 0) {
        os << '-';
        n = -n;
    }
    std::string s;
    while (n > 0) {
        s += '0' + (n % 10);
        n /= 10;
    }
    std::reverse(s.begin(), s.end());
    return os << s;
}
#ifndef XCPC_STRING_ALPHABET_HPP
#define XCPC_STRING_ALPHABET_HPP

struct LowercaseAlphabet {
    static constexpr int size = 26;

    static int id(unsigned char c) {
        if ('a' <= c && c <= 'z') return c - 'a';
        return -1;
    }
};

struct AlnumAlphabet {
    static constexpr int size = 62;

    static int id(unsigned char c) {
        if ('a' <= c && c <= 'z') return c - 'a';
        if ('A' <= c && c <= 'Z') return c - 'A' + 26;
        if ('0' <= c && c <= '9') return c - '0' + 52;
        return -1;
    }
};

#endif

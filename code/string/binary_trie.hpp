#ifndef XCPC_STRING_BINARY_TRIE_HPP
#define XCPC_STRING_BINARY_TRIE_HPP

template<int B = 64>
class BinaryTrie {
    static_assert(1 <= B && B <= 64);
    using U64 = uint64_t;

public:
    void insert(U64 x) {
        int u = 0;
        ++tr[u].cnt;
        for (int i = B - 1; i >= 0; --i) {
            int b = (x >> i) & 1;
            if (!tr[u].ch[b]) {
                tr[u].ch[b] = static_cast<int>(tr.size());
                tr.emplace_back();
            }
            u = tr[u].ch[b];
            ++tr[u].cnt;
        }
    }

    bool erase(U64 x) {
        array<int, B + 1> path{};
        int u = 0;
        for (int i = B - 1; i >= 0; --i) {
            u = tr[u].ch[(x >> i) & 1];
            if (!u || !tr[u].cnt) return false;
            path[B - i] = u;
        }
        for (int v : path) --tr[v].cnt;
        return true;
    }

    optional<U64> maxXor(U64 x) const {
        if (!tr[0].cnt) return nullopt;
        int u = 0;
        U64 ans = 0;
        for (int i = B - 1; i >= 0; --i) {
            int b = (x >> i) & 1;
            int v = tr[u].ch[b ^ 1];
            if (v && tr[v].cnt) {
                ans |= U64{1} << i;
                u = v;
            } else {
                u = tr[u].ch[b];
            }
        }
        return ans;
    }

private:
    struct Node {
        array<int, 2> ch{};
        int cnt = 0;
    };

    vector<Node> tr{Node{}};
};

#endif

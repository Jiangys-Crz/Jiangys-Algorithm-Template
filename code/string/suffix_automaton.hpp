using ll = long long;

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

#ifndef XCPC_STRING_SUFFIX_AUTOMATON_HPP
#define XCPC_STRING_SUFFIX_AUTOMATON_HPP

template<class Alphabet = LowercaseAlphabet>
class SAM {
public:
    SAM() = default;

    explicit SAM(string_view s) {
        for (unsigned char c : s) extend(c);
    }

    void extend(unsigned char c) {
        int x = Alphabet::id(c);
        assert(x >= 0 && x < Alphabet::size);
        int cur = static_cast<int>(tr.size());
        tr.emplace_back();
        tr[cur].len = tr[last].len + 1;
        tr[cur].cnt = 1;
        int p = last;
        while (p >= 0 && !tr[p].ch[x]) {
            tr[p].ch[x] = cur;
            p = tr[p].link;
        }
        if (p < 0) {
            tr[cur].link = 0;
        } else {
            int q = tr[p].ch[x];
            if (tr[p].len + 1 == tr[q].len) {
                tr[cur].link = q;
            } else {
                Node state = tr[q];
                state.len = tr[p].len + 1;
                state.cnt = 0;
                int clone = static_cast<int>(tr.size());
                tr.push_back(state);
                while (p >= 0 && tr[p].ch[x] == q) {
                    tr[p].ch[x] = clone;
                    p = tr[p].link;
                }
                tr[q].link = tr[cur].link = clone;
            }
        }
        last = cur;
    }

    int state(string_view s) const {
        int u = 0;
        for (unsigned char c : s) {
            int x = Alphabet::id(c);
            if (x < 0 || x >= Alphabet::size || !tr[u].ch[x]) return -1;
            u = tr[u].ch[x];
        }
        return u;
    }

    ll distinctSubstrings() const {
        ll ans = 0;
        for (size_t u = 1; u < tr.size(); ++u) {
            ans += tr[u].len - tr[tr[u].link].len;
        }
        return ans;
    }

    vector<ll> occurrenceCounts() const {
        vector<int> bucket(tr[last].len + 1), ord(tr.size());
        vector<ll> cnt(tr.size());
        for (const Node& node : tr) ++bucket[node.len];
        for (size_t i = 1; i < bucket.size(); ++i) bucket[i] += bucket[i - 1];
        for (int u = static_cast<int>(tr.size()) - 1; u >= 0; --u) {
            ord[--bucket[tr[u].len]] = u;
            cnt[u] = tr[u].cnt;
        }
        cnt[0] = 1;
        for (auto it = ord.rbegin(); it != ord.rend(); ++it) {
            int u = *it, p = tr[u].link;
            if (p >= 0) cnt[p] += cnt[u];
        }
        return cnt;
    }

private:
    struct Node {
        array<int, Alphabet::size> ch{};
        int len = 0, link = -1, cnt = 0;
    };

    vector<Node> tr{Node{}};
    int last = 0;
};

#endif

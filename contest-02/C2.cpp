#ifndef ONPC
//#pragma GCC optimize("O3")
//#pragma GCC target("avx,sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,lzcnt")
//#pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <utility>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <functional>
#include <string>
#include <numeric>
#include <set>
#include <array>
#include <cassert>
#include <map>
#include <unordered_map>
#include <deque>
#include <stack>
#include <unordered_set>

//#define int int64_t

using namespace std;
using ll = int64_t;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vc = vector<char>;
using vvc = vector<vc>;
using ui = uint32_t;
using ull = uint64_t;
using ld = long double;
//using i128 = __int128;

#define all(x) (x).begin(), (x).end()
#define endl '\n'

const int ALPHABET = 26 * 2 + 10;

int ord(char c) {
    if ('0' <= c && c <= '9')
        return c - '0';
    if ('A' <= c && c <= 'Z')
        return c - 'A' + 10;
    if ('a' <= c && c <= 'z')
        return c - 'a' + 36;
}

char chr(int c) {
    if (0 <= c && c <= 9)
        return c + '0';
    if (10 <= c && c <= 35)
        return (c - 10) + 'A';
    if (36 <= c && c <= 61)
        return (c - 36) + 'a';
}

int encode(char c0, char c1) {
    return ord(c0) * ALPHABET + ord(c1);
}

pair<char, char> decode(int v) {
    return {chr(v / ALPHABET), chr(v % ALPHABET)};
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    array<vi, ALPHABET * ALPHABET> g{};
    array<int, ALPHABET * ALPHABET> in{0}, out{0};
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        int f = encode(s[0], s[1]);
        int t = encode(s[1], s[2]);
        g[f].push_back(t);
        ++out[f];
        ++in[t];
    }


    int from = -1;
    int to = -1;
    bool in_found = false;
    bool out_found = false;
    bool is_euler = true;
    for (int i = 0; i < ALPHABET * ALPHABET; ++i) {
        if (out[i] - in[i] == 1) {
            if (in_found) {
                is_euler = false;
                break;
            }
            from = i;
            in_found = true;
        } else if (in[i] - out[i] == 1) {
            if (out_found) {
                is_euler = false;
                break;
            }
            out_found = true;
            to = i;
        } else if (in[i] != out[i]) {
            is_euler = false;
            break;
        }
    }
    if (!in_found) {
        for (int i = 0; i < ALPHABET * ALPHABET; ++i) {
            if (!g[i].empty()) {
                from = i;
                break;
            }
        }
    }
    if (!is_euler) {
        cout << "NO" << endl;
        return 0;
    }

    vi path;
    auto dfs = [&g, &path](int v, const auto &rec) -> void {
        while (!g[v].empty()) {
            int to = g[v].back();
            g[v].pop_back();
            rec(to, rec);
        }
        path.push_back(v);
    };
    dfs(from, dfs);
    if (path.size() != n + 1) {
        cout << "NO" << endl;
        return 0;
    }
    reverse(all(path));
    cout << "YES" << endl;
    for (int i = 0; i < n + 1; ++i)
        cout << decode(path[i]).first;
    cout << decode(path.back()).second;
    cout << endl;
}
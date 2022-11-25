#ifndef ONPC
#pragma GCC optimize("O3")
#pragma GCC target("avx2,avx,sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,lzcnt")
#pragma GCC optimize("unroll-loops")
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
#include <bitset>

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
#define nl '\n'

template<typename T>
istream& operator>>(istream& s, vector<T>& v) {
    for (auto &&el : v)
        s >> el;
    return s;
}

template<typename T>
ostream& operator<<(ostream& s, const vector<T>& v) {
    for (auto &&el : v)
        s << el << ' ';
    s << '\n';
    return s;
}

const ll MOD = 1e9 + 7;
using mat = array<array<ll, 4>, 4>;
const mat I{array<ll, 4>{-1, 0, 0, 0},
            array<ll, 4>{0, 1, 0, 0},
            array<ll, 4>{0, 0, 1, 0},
            array<ll, 4>{0, 0, 0, 1}};

mat operator*(const mat &a, const mat &b) {
    if (a[0][0] == -1)
        return b;
    if (b[0][0] == -1)
        return a;
    mat c;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            c[i][j] = 0;
            for (int k = 0; k < 4; ++k) {
                c[i][j] += a[i][k] * b[k][j];
                c[i][j] %= MOD;
            }
        }
    }
    return c;
}

struct segtree {
    int n;
    vector<mat> t;

    segtree(const vector<mat> &a) {
        n = a.size();
        t.resize(4 * n);
        build(a, 1, 0, n);
    }

    void build(const vector<mat> &a, int v, int l, int r) {
        if (l + 1 == r) {
            t[v] = a[l];
            return;
        }

        int m = (l + r) / 2;
        build(a, 2 * v, l, m);
        build(a, 2 * v + 1, m, r);
        t[v] = t[2 * v] * t[2 * v + 1];
    }

    mat get(int ql, int qr, int v = 1, int l = 0, int r = -1) {
        if (r == -1)
            r = n;
        if (ql <= l && r <= qr)
            return t[v];
        if (qr <= l || r <= ql)
            return I;

        int m = (l + r) / 2;
        return get(ql, qr, 2 * v, l, m) * get(ql, qr, 2 * v + 1, m, r);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<mat> a(n);
    for (auto& e : a) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                cin >> e[i][j];
            }
        }
    }
    segtree seg(a);
    while (q--) {
        int l, r;
        cin >> l >> r;
        --l;
        mat m = seg.get(l, r);
        ll ans = 0;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                ans ^= m[i][j];
            }
        }
        cout << ans << ' ';
    }
    cout << nl;
}
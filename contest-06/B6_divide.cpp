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

ll mat_xor(const mat &a) {
    ll ans = 0;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            ans ^= a[i][j];
    return ans;
}

struct query {
    int l, r, id;
};

bool operator==(const query &a, const query &b) {
    return a.id == b.id;
}

struct qhash {
    size_t operator()(const query &a) const {
        hash<int> h{};
        return h(a.id);
    }
};

void solve(const vector<mat> &a, unordered_set<query, qhash> &qs, vll &ans, int l, int r) {
    if (r - l == 0)
        return;
    if (r - l == 1) {
        for (auto it = qs.begin(); it != qs.end();) {
            if (it->l == l && it->r == r) {
                ans[it->id] = mat_xor(a[l]);
                it = qs.erase(it);
            } else {
                ++it;
            }
        }
        return;
    }
    int m = (l + r) / 2;
    vector<mat> lp(m - l + 1, I), rp(r - m + 1, I);
    for (int i = 1; i < m - l + 1; ++i)
        lp[i] = a[m - i] * lp[i - 1];
    for (int i = 1; i < r - m + 1; ++i)
        rp[i] = rp[i - 1] * a[m + i - 1];
    for (auto it = qs.begin(); it != qs.end();) {
        if (l <= it->l && it->l <= m && m <= it->r && it->r <= r) {
            ans[it->id] = mat_xor(lp[m - it->l] * rp[it->r - m]);
            it = qs.erase(it);
        } else {
            ++it;
        }
    }
    solve(a, qs, ans, l, m);
    solve(a, qs, ans, m, r);
}

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
    unordered_set<query, qhash> qs;
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        --l;
        qs.insert({l, r, i});
    }
    vll ans(q);
    solve(a, qs, ans, 0, n);
    cout << ans;
}
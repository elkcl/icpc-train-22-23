#ifndef ONPC
#pragma GCC optimize("O3")
#pragma GCC target("avx2,avx,sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,lzcnt")
#pragma GCC optimize("unroll-loops")
#endif

#include <bits/stdc++.h>

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
using mat = array<int, 16>;

mat operator*(const mat &a, const mat &b) {
    if (a[0] == -1)
        return b;
    if (b[0] == -1)
        return a;
    mat c{};
    for (int i = 0; i < 4; ++i) {
        for (int k = 0; k < 4; ++k) {
            for (int j = 0; j < 4; ++j) {
                c[(i << 2) + j] = (c[(i << 2) + j] + 1ll * a[(i << 2) + k] * b[(k << 2) + j]) % MOD;
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
        t.resize(2 * n);
        for (int i = 0; i < n; ++i)
            t[n + i] = a[i];
        for (int i = n - 1; i > 0; --i)
            t[i] = t[i << 1] * t[(i << 1) | 1];
    }

    mat get(int l, int r) {
        mat left_ans{};
        mat right_ans{};
        left_ans[0] = right_ans[0] = -1;
        l += n;
        r += n;
        while (l < r) {
            if (l & 1)
                left_ans = left_ans * t[l++];
            if (r & 1)
                right_ans = t[--r] * right_ans;
            l >>= 1;
            r >>= 1;
        }
        return left_ans * right_ans;
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
                cin >> e[(i << 2) + j];
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
                ans ^= m[(i << 2) + j];
            }
        }
        cout << ans << ' ';
    }
    cout << nl;
}
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

struct fenwick {
    vll t;
    int n;

    fenwick(int _n) {
        n = _n;
        t.resize(n + 1, 0);
    }

    ll sum(int r) {
        ll ans = 0;
        for (; r > 0; r -= r & -r)
            ans += t[r];
        return ans;
    }

    ll sum(int l, int r) {
        return sum(r) - sum(l);
    }

    void add(int i, ll x) {
        ++i;
        for (; i <= n; i += i & -i)
            t[i] += x;
    }
};


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vi a(n);
    cin >> a;
    vi inv(n);
    for (int i = 0; i < n; ++i) {
        inv[a[i] - 1] = i;
    }
    vector<fenwick> fw(k + 1, fenwick(n));
    fw[0].add(inv[0], 1);
    for (int i = 1; i < n; ++i) {
        fw[0].add(inv[i], 1);
        for (int j = 1; j < k + 1; ++j) {
            fw[j].add(inv[i], fw[j - 1].sum(inv[i]));
        }
    }
    cout << fw[k].sum(n) << nl;
}
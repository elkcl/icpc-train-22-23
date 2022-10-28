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

    int n, q;
    cin >> n >> q;
    vll a(n);
    cin >> a;
    fenwick fw(n);
    for (int i = 0; i < n; ++i)
        fw.add(i, a[i]);
    while (q--) {
        int t;
        ll x, y;
        cin >> t >> x >> y;
        if (t == 1) {
            cout << fw.sum(x - 1, y) << nl;
        } else {
            fw.add(x - 1, y - a[x - 1]);
            a[x - 1] = y;
        }
    }
}
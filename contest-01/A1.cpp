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
#define fast_io ios_base::sync_with_stdio(false); cin.tie(nullptr);
#define endl '\n'

struct dsu {
    vi p;
    vi rank;

    dsu(int n) {
        p.resize(n);
        rank.resize(n, 1);
        iota(all(p), 0);
    }

    int root(int x) {
        if (p[x] == x)
            return x;
        return p[x] = root(p[x]);
    }

    void unite(int a, int b) {
        a = root(a);
        b = root(b);
        if (a == b)
            return;
        if (rank[a] < rank[b])
            swap(a, b);
        p[b] = a;
    }
};

struct edge {
    int f, t;
    ll w;
};

signed main() {
    fast_io

    int n, m;
    cin >> n >> m;
    vector<edge> eds(m);
    for (auto &el : eds) {
        cin >> el.f >> el.t >> el.w;
        --el.f, --el.t;
    }
    sort(all(eds), [](const edge &a, const edge &b) -> bool {
        return a.w < b.w;
    });
    ll ans = 0;
    auto d = dsu(n);
    for (auto &el : eds) {
        if (d.root(el.f) != d.root(el.t)) {
            d.unite(el.f, el.t);
            ans += el.w;
        }
    }
    cout << ans << endl;
}
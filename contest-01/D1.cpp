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
        rank[a] += rank[b];
    }
};

struct edge {
    int f, t;
    ll w;
};

struct vertex {
    int v;
    ll w;
};

signed main() {
    fast_io

    int n, m;
    cin >> n >> m;
    vector<vertex> ws(n);
    for (int i = 0; i < n; ++i) {
        ws[i].v = i;
        cin >> ws[i].w;
    }
    sort(all(ws), [](const vertex &a, const vertex &b) -> bool {
        return a.w < b.w;
    });
    vector<edge> eds(n - 1);
    eds.reserve(n + m);
    for (int i = 0 ; i < n - 1; ++i) {
        eds[i].f = ws[0].v;
        eds[i].t = ws[i + 1].v;
        eds[i].w = ws[0].w + ws[i + 1].w;
    }
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll c;
        cin >> u >> v >> c;
        --u, --v;
        eds.push_back({u, v, c});
    }
    sort(all(eds), [](const edge &a, const edge &b) -> bool {
        return a.w < b.w;
    });
    auto d = dsu(n);
    ll ans = 0;
    for (auto &&[f, t, w] : eds) {
        if (d.root(f) != d.root(t)) {
            ans += w;
            d.unite(f, t);
        }
    }
    cout << ans << endl;
}
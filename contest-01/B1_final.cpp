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

struct edge {
    int f, t;
    ll w;
};

struct dsu {
    vi p;
    vll rank;
//    vi paths;

    dsu(int n) {
        p.resize(n);
        rank.resize(n, 1);
//        paths.resize(n, 0);
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
//        paths[a] += paths[b] + rank[a] * rank[b];
        rank[a] += rank[b];
    }
};

signed main() {
    fast_io

    int n, q;
    cin >> n >> q;
    vector<edge> eds(n - 1);
    for (auto &e : eds) {
        cin >> e.f >> e.t >> e.w;
        --e.f, --e.t;
    }
    vll qs(q);
    for (auto &e : qs)
        cin >> e;
    vll sqs(qs);
    sort(all(eds), [](const edge &a, const edge &b) -> bool {
        return a.w < b.w;
    });
    sort(all(sqs));
    vll ans(q, 0);
    auto d = dsu(n);
    int curr = 0;
    ll psum = 0;
    for (auto&& [f, t, w] : eds) {
        while (w > sqs[curr]) {
            ans[curr] = psum;
            ++curr;
            if (curr >= q)
                goto OUT;
        }
        psum += d.rank[d.root(f)] * d.rank[d.root(t)];
        d.unite(f, t);
    }
    OUT:;
    for (int i = curr; i < q; ++i)
        ans[i] = psum;
    for (int i = 0; i < q; ++i) {
        auto ind = lower_bound(all(sqs), qs[i]) - sqs.begin();
        cout << ans[ind] << ' ';
    }
    cout << endl;
}
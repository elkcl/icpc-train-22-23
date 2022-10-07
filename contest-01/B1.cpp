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
    int t;
    ll w;
};

int q;
vector<vector<edge>> g;
vc used;
vi s;
vi sqs;
vi ans;

int sizes(int v, int p) {
    for (auto [t, w] : g[v]) {
        if (!used[t] && t != p)
            s[v] += sizes(t, v);
    }
    return s[v];
}

int centroid(int v, int p, int n) {
    for (auto [t, w] : g[v]) {
        if (!used[t] && t != p && s[t] > n / 2)
            return centroid(t, v, n);
    }
    return v;
}

void dfs(int v, int p, ll m, vi &arr) {
    auto i = lower_bound(all(sqs), m) - sqs.begin();
    if (i < q)
        ++arr[i];
    for (auto [t, w] : g[v]) {
        if (!used[t] && t != p)
            dfs(t, v, max(m, w), arr);
    }
}

void solve(int v) {
    sizes(v, -1);
    vi d(q, 1);
    vi d1(q, 1);
    for (auto [t, w] : g[v]) {
        if (!used[t]) {
            vi arr(q, 0);
            arr[0] = 1;
            dfs(t, v, w, arr);
            for (int i = 1; i < q; ++i)
                arr[i] += arr[i - 1];
            for (int i = 0; i < q; ++i) {
                d[i] *= arr[i];
                d1[i] *= arr[i] - 1;
            }
        }
    }
    for (int i = 0; i < q; ++i)
        ans[i] += d[i] - d1[i] - 1;

    used[v] = true;
    for (auto [t, w] : g[v])
        if (!used[t])
            solve(centroid(t, v, s[t]));
}

signed main() {
    fast_io

    int n;
    cin >> n >> q;
    g.resize(n);
    used.resize(n, false);
    s.resize(n, 1);
    vi qs(q);
    ans.resize(q, 0);

    for (int i = 0; i < n - 1; ++i) {
        int f, t;
        ll w;
        cin >> f >> t >> w;
        --f, --t;
        g[f].push_back({t, w});
        g[t].push_back({f, w});
    }
    for (int i = 0; i < q; ++i)
        cin >> qs[i];
    sqs = qs;
    sort(all(sqs));
    sizes(0, -1);
    solve(centroid(0, -1, n));
    for (int i = 0; i < q; ++i) {
        auto ind = lower_bound(all(sqs), qs[i]) - sqs.begin();
        cout << ans[ind] << ' ';
    }
    cout << endl;
}
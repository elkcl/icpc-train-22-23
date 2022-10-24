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


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vi arr(n);
    cin >> arr;
    vvi f(n);
    int sz = 0;
    for (int i = 0; i < n; ++i) {
        int curr = arr[i];
        while (curr % 2 == 0) {
            f[i].push_back(2);
            ++sz;
            curr /= 2;
        }
        for (int d = 3; d * d <= n; d += 2) {
            while (curr % d == 0) {
                f[i].push_back(d);
                ++sz;
                curr /= d;
            }
        }
        if (curr != 1) {
            f[i].push_back(curr);
            ++sz;
        }
    }
    vi pref(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i - 1] + f[i - 1].size();
    }

    vvi g(sz);
    vi lr(sz, -1), rl(sz, -1), used(sz, 0);
    for (int q = 0; q < m; ++q) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        if (a % 2 == 1)
            swap(a, b);
        for (int i = 0; i < f[a].size(); ++i) {
            for (int j = 0; j < f[b].size(); ++j) {
                if (f[a][i] == f[b][j])
                    g[pref[a] + i].push_back(pref[b] + j);
            }
        }
    }

    int curr = 1;
    auto dfs = [&g, &used, &lr, &rl, &curr](const auto &rec, int v) -> bool {
        if (used[v] == curr)
            return false;
        used[v] = curr;
        for (int to : g[v]) {
            if (rl[to] == -1 || rec(rec, rl[to])) {
                rl[to] = v;
                lr[v] = to;
                return true;
            }
        }
        return false;
    };
    ll ans = 0;
    for (bool run = true; run;) {
        run = false;
        ++curr;
        for (int i = 0; i < sz; ++i) {
            if (lr[i] == -1 && dfs(dfs, i)) {
                run = true;
                ++ans;
            }
        }
    }
    cout << ans << endl;
}
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


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, m;
    cin >> n >> k >> m;
    vvi g(k);
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        g[r].push_back(l);
    }
    vi lr(k, -1), rl(n, -1);
    vi used(k, 0);
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
        for (int i = 0; i < k; ++i) {
            if (lr[i] == -1 && dfs(dfs, i)) {
                run = true;
                ++ans;
            }
        }
    }
    cout << ans << endl;
}
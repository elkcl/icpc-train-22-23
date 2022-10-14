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

    int n;
    cin >> n;
    vector<string> v(n);
    for (auto &e : v)
        cin >> e;
    array<unordered_set<int>, 26> g{};
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            auto sz = min(v[i].size(), v[j].size());
            bool prefix = true;
            for (int k = 0; k < sz; ++k) {
                if (v[i][k] == v[j][k])
                    continue;
                g[v[i][k] - 'a'].insert(v[j][k] - 'a');
                prefix = false;
                break;
            }
            if (prefix && v[i].size() > v[j].size()) {
                cout << "Impossible" << endl;
                return 0;
            }
        }
    }

    array<int, 26> used{0};
    vi ans;
    auto dfs = [&g, &used, &ans](int v, const auto &rec) -> bool {
        used[v] = 1;
        for (auto to : g[v]) {
            if (used[to] == 1) {
                return true;
            } else if (used[to] == 0) {
                bool res = rec(to, rec);
                if (res)
                    return true;
            }
        }
        used[v] = 2;
        ans.push_back(v);
        return false;
    };
    for (int i = 0; i < 26; ++i) {
        if (used[i])
            continue;
        bool res = dfs(i, dfs);
        if (res) {
            cout << "Impossible" << endl;
            return 0;
        }
    }
    reverse(all(ans));
    for (auto &e : ans)
        cout << static_cast<char>(e + 'a');
    cout << endl;
}
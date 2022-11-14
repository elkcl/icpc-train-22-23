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
#include <bitset>

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

const int BLOCK = 300;
const int MAXN = 100001;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;
    vll a(n);
    cin >> a;
    int bls = 0;
    vi heavy_id(m, -1);
    vector<bitset<MAXN>> heavy_contains;
    vll heavy_base;
    vll heavy_add;
    vvi sets(m);
    for (int i = 0; i < m; ++i) {
        int k;
        cin >> k;
        sets[i].resize(k);
        if (k > BLOCK) {
            heavy_id[i] = bls;
            heavy_contains.emplace_back();
            heavy_base.push_back(0);
            heavy_add.push_back(0);
            for (int j = 0; j < k; ++j) {
                cin >> sets[i][j];
                --sets[i][j];
                heavy_contains[bls][sets[i][j]] = true;
                heavy_base[bls] += a[sets[i][j]];
            }
            ++bls;
        } else {
            for (int j = 0; j < k; ++j) {
                cin >> sets[i][j];
                --sets[i][j];
            }
        }
    }
    vvi intersect(bls, vi(m, 0));
    for (int i = 0; i < bls; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int e : sets[j]) {
                if (heavy_contains[i][e])
                    ++intersect[i][j];
            }
        }
    }

    while (q--) {
        char t;
        cin >> t;
        if (t == '+') {
            int k, x;
            cin >> k >> x;
            --k;
            if (heavy_id[k] == -1) {
                for (int e : sets[k])
                    a[e] += x;
                for (int i = 0; i < bls; ++i)
                    heavy_base[i] += 1ll * x * intersect[i][k];
            } else {
                heavy_add[heavy_id[k]] += x;
            }
        } else {
            int k;
            cin >> k;
            --k;
            if (heavy_id[k] == -1) {
                ll ans = 0;
                for (int e : sets[k])
                    ans += a[e];
                for (int i = 0; i < bls; ++i)
                    ans += 1ll * heavy_add[i] * intersect[i][k];
                cout << ans << nl;
            } else {
                ll ans = heavy_base[heavy_id[k]];
                for (int i = 0; i < bls; ++i)
                    ans += 1ll * heavy_add[i] * intersect[i][k];
                cout << ans << nl;
            }
        }
    }
}
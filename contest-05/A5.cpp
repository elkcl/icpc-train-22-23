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

struct query {
    int l, r, id;
};

const int BLOCK = 300;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vi a(n);
    cin >> a;
    vll ans(m);
    vi pref(n + 1, 0);
    for (int i = 0; i < n; ++i)
        pref[i + 1] = pref[i] ^ a[i];
    int bls = n / BLOCK + (n % BLOCK != 0);
    vector<vector<query>> b(bls);
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        --l, --r;
        b[l / BLOCK].push_back({l, r, i});
    }
    for (int i = 0; i < bls; ++i) {
        sort(all(b[i]), [](const query &a, const query &b) -> bool {
            return a.r < b.r;
        });
        int l = i * BLOCK, r = l - 1;
        vi cnt(1 << 20, 0);
        cnt[pref[l]] = 1;
        ll curr = 0;
        auto add = [&cnt, &curr, k](int x) -> void {
            curr += cnt[x ^ k];
            ++cnt[x];
        };
        auto del = [&cnt, &curr, k](int x) -> void {
            --cnt[x];
            curr -= cnt[x ^ k];
        };
        for (auto &q : b[i]) {
            while (r < q.r) {
                ++r;
                add(pref[r + 1]);
            }
            while (l > q.l) {
                --l;
                add(pref[l]);
            }
            while (l < q.l) {
                del(pref[l]);
                ++l;
            }
            ans[q.id] = curr;
        }
    }
    for (int i = 0; i < m; ++i)
        cout << ans[i] << nl;
}
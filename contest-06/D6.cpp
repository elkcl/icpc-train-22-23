#ifndef ONPC
#pragma GCC optimize("O3")
#pragma GCC target("avx2,avx,sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,lzcnt")
#pragma GCC optimize("unroll-loops")
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

ll solve(const vll &a, const vi &pcnt, bool rev, int l, int r) {
    if (r - l == 0)
        return 0;
    if (r - l == 1) {
        return 1;
    }
    int m = (l + r) / 2;
    if (rev)
        m = (l + r) - m;
    int minl = m - 1;
    int maxl = m - 1;
    int r0 = m;
    int r1 = m;
    array<int, 64> r0c{0}, r1c{0};
    int r0min = m;
    int r1min = m;
    ll ans = 0;
    for (int i = m - 1; i >= l; --i) {
        if (a[i] < a[minl])
            minl = i;
        if (a[i] > a[maxl])
            maxl = i;
        while (r0 < r && a[r0] >= a[minl]) {
            if (a[r0] < a[r0min])
                r0min = r0;
            ++r0c[pcnt[r0min]];
            ++r0;
        }
        if (!rev) {
            while (r1 < r && a[r1] <= a[maxl]) {
                if (a[r1] < a[r1min])
                    r1min = r1;
                ++r1c[pcnt[r1min]];
                ++r1;
            }
        } else {
            while (r1 < r && a[r1] < a[maxl]) {
                if (a[r1] < a[r1min])
                    r1min = r1;
                ++r1c[pcnt[r1min]];
                ++r1;
            }
        }
        if (r1 >= r0) {
            if (pcnt[minl] == pcnt[maxl])
                ans += r0 - m;
            ans += r1c[pcnt[maxl]] - r0c[pcnt[maxl]];
        } else {
            if (pcnt[minl] == pcnt[maxl])
                ans += r1 - m;
        }
    }
    return ans + solve(a, pcnt, rev, l, m) + solve(a, pcnt, rev, m, r);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vll a(n);
    for (auto &e : a)
        cin >> e;
    vi pcnt(n);
    for (int i = 0; i < n; ++i)
        pcnt[i] = __builtin_popcountll(a[i]);
    ll ans = solve(a, pcnt, false, 0, n);
    reverse(all(a));
    reverse(all(pcnt));
    ans += solve(a, pcnt, true, 0, n);
    cout << ans - n << nl;
}
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

void solve(vii &ans, int l, int r) {
    if (r - l <= 1) {
        return;
    }
    if (r - l == 2) {
        ans.emplace_back(l, l + 1);
        return;
    }

    int m = (l + r) / 2;
    solve(ans, l, m);
    solve(ans, m, r);
    for (int i = l, j = m; i < m; ++i, ++j)
        ans.emplace_back(i, j);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vii ans;
    ans.reserve(5e5);
    int k = 1;
    while (2 * k <= n)
        k *= 2;
    solve(ans, 0, k);
    if (k != n)
        solve(ans, n - k, n);
    cout << ans.size() << nl;
    for (auto&& [a, b] : ans)
        cout << a + 1 << ' ' << b + 1 << nl;
}
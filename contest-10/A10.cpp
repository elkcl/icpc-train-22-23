#ifndef ONPC
#pragma GCC optimize("O3")
#pragma GCC target("avx2,avx,sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,lzcnt")
//#pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <iomanip>
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

#include <ext/pb_ds/assoc_container.hpp>

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
using namespace __gnu_pbds;

#define all(x) (x).begin(), (x).end()
#define nl endl

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

vi pref_func(const string &str) {
    int n = str.size();
    vi p(n, 0);
    p[0] = 0;
    for (int i = 1; i < n; ++i) {
        int k = p[i - 1];
        while (k > 0 && str[i] != str[k])
            k = p[k - 1];
        if (str[i] == str[k])
            ++k;
        p[i] = k;
    }
    return p;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, t;
    cin >> s >> t;
    int sn = s.size(), tn = t.size();
    auto p = pref_func(t);
    string add = t.substr(p[tn - 1]);
    int s0, s1, t0, t1, add0, add1;
    s0 = s1 = t0 = t1 = add0 = add1 = 0;
    for (auto c : s) {
        if (c == '0')
            ++s0;
        else
            ++s1;
    }
    for (auto c : t) {
        if (c == '0')
            ++t0;
        else
            ++t1;
    }
    for (auto c : add) {
        if (c == '0')
            ++add0;
        else
            ++add1;
    }
    if (t0 > s0 || t1 > s1) {
        cout << string(s0, '0') << string(s1, '1') << nl;
        return 0;
    }
    s0 -= t0;
    s1 -= t1;
    cout << t;
    while (s0 >= add0 && s1 >= add1) {
        s0 -= add0;
        s1 -= add1;
        cout << add;
    }
    cout << string(s0, '0') << string(s1, '1') << nl;
}
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

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int n = s.size();
        int k = 0;
        while (k < n / 2 && s[k] == s[n - k - 1])
            ++k;
        string a = s.substr(k, n - 2 * k);
        string s2(a);
        reverse(all(s2));
        string s1(a);
        s1 += "#";
        s1 += s2;
        s2 += "#";
        s2 += a;
        auto p1 = pref_func(s1);
        auto p2 = pref_func(s2);
        if (p1.back() > p2.back()) {
            cout << s.substr(0, k + p1.back()) << s.substr(n - k) << nl;
        } else {
            cout << s.substr(0, k) << s.substr(n - k - p2.back()) << nl;
        }
    }
}
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

const ll MOD = 998'244'353;
const ll BLOCK = 500;
const ll G = 3;

ll binpow(ll a, ll k, ll m) {
    if (k == 0)
        return 1;
    if (k % 2 == 0) {
        ll res = binpow(a, k / 2, m);
        return (res * res) % m;
    } else {
        ll res = binpow(a, k - 1, m);
        return (res * a) % m;
    }
}

ll dlog(ll a, ll b, unordered_map<ll, ll> &fs) {
    ll curr = b;
    for (int i = 0; i <= BLOCK; ++i) {
        if (fs.find(curr) != fs.end()) {
            ll ans = fs[curr] * BLOCK - i;
            if (ans < MOD)
                return ans;
        }
        curr = (curr * a) % MOD;
    }
    return -1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    ll an = binpow(G, BLOCK, MOD);
    unordered_map<ll, ll> fs;
    ll curr = an;
    for (int i = 1; i <= MOD / BLOCK + 1; ++i) {
        if (fs.find(curr) == fs.end())
            fs[curr] = i;
        curr = (curr * an) % MOD;
    }
    ll d = MOD - 1;
    for (int i = 0; i < n; ++i) {
        ll e;
        cin >> e;
        d = gcd(d, dlog(G, e, fs));
    }
    cout << (MOD - 1) / d << nl;
}
#ifndef ONPC
//#pragma GCC optimize("O3")
//#pragma GCC target("avx,sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,lzcnt")
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

const ld PI = acos(-1);
const ld EPS = 1e-7;

struct Point {
    ll x, y;

    ll abs2() const {
        return x * x + y * y;
    }
};

Point operator+(const Point &a, const Point &b) {
    return {a.x + b.x, a.y + b.y};
}

Point operator-(const Point &a) {
    return {-a.x, -a.y};
}

Point operator-(const Point &a, const Point &b) {
    return a + (-b);
}

Point operator*(ll k, const Point &a) {
    return {k * a.x, k * a.y};
}

Point operator*(const Point &a, ll k) {
    return k * a;
}

ll operator*(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}

ll operator%(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

ld operator^(const Point &a, const Point &b) {
     ld ang = atan2l(a % b, a * b);
     if (ang < 0)
         return ang + 2*PI;
    return ang;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Point> v(n);
    for (auto &el : v)
        cin >> el.x >> el.y;
    sort(all(v), [](const Point &a, const Point &b) -> bool {
        Point p{1, 0};
        return (p ^ a) < (p ^ b);
    });
    ld maxang = 0;
    for (int i = 0; i < n - 1; ++i) {
        maxang = max(maxang, v[i] ^ v[i + 1]);
    }
    if (abs(v[n - 1] ^ v[0]) < EPS)
        maxang = 2*PI;
    else
        maxang = max(maxang, v[n - 1] ^ v[0]);
    maxang = 2*PI - maxang;
    ld ans = maxang * 180 / PI;
    cout << fixed << setprecision(10) << ans << nl;
}
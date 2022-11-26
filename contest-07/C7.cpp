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

bool operator==(const Point &a, const Point &b) {
    return a.x == b.x && a.y == b.y;
}

Point mirror(const Point &o, const Point &a) {
    return a + 2 * (o - a);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll k;
    cin >> n >> k;
    Point p{};
    cin >> p.x >> p.y;
    vector<Point> v(n);
    for (auto& el : v)
        cin >> el.x >> el.y;
    Point a{0, 0}, b{0, 1};
    Point a1{a}, b1{b};
    for (int i = 0; i < n; ++i) {
        a1 = mirror(v[i], a1);
        b1 = mirror(v[i], b1);
    }
    Point ans{p};
    if ((a - b) == (a1 - b1)) {
        Point t = (a1 - a) * (k / n);
        ans = ans + t;
    } else if ((k / n) % 2 != 0) {
        //assert((a - b) % (a1 - b1) == 0);
        ld x = 1.0l * (b.x + b1.x) / 2;
        ld y = 1.0l * (b.y + b1.y) / 2;
        Point t{};
        t.x = static_cast<ll>(2 * (x - ans.x));
        t.y = static_cast<ll>(2 * (y - ans.y));
        ans = ans + t;
    }
    for (int i = 0; i < k % n; ++i) {
        ans = mirror(v[i], ans);
    }
    cout << ans.x << ' ' << ans.y << nl;
}
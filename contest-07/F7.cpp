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
    return atan2l(a % b, a * b);
}

bool operator==(const Point &a, const Point &b) {
    return a.x == b.x && a.y == b.y;
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Point> p(n);
    for (auto& el : p)
        cin >> el.x >> el.y;
    reverse(all(p));
    int m;
    cin >> m;
    vector<Point> b(m);
    for (auto& el : b)
        cin >> el.x >> el.y;
    vector<ld> angles(n);
    angles[0] = angles[1] = 0;
    Point base = p[1] - p[0];
    for (int i = 2; i < n; ++i) {
        angles[i] = base ^ (p[i] - p[0]);
    }
    for (int i = 0; i < m; ++i) {
        ld curr = base ^ (b[i] - p[0]);
        auto it = upper_bound(all(angles), curr);
        if (it == angles.begin() || it == angles.end()) {
            cout << "NO" << nl;
            return 0;
        }
        int x = it - angles.begin();
        ll p1 = (p[x - 1] - p[0]) % (b[i] - p[0]);
        ll p2 = (p[x] - p[x - 1]) % (b[i] - p[x - 1]);
        ll p3 = (p[0] - p[x]) % (b[i] - p[x]);
        if (p1 < 0 || p2 <= 0 || p3 < 0) {
            cout << "NO" << nl;
            return 0;
        }
        ll p0 = (p[1] - p[0]) % (b[i] - p[0]);
        ll pn = (p[n - 1] - p[0]) % (b[i] - p[0]);
        if (p0 == 0 || pn == 0) {
            cout << "NO" << nl;
            return 0;
        }
        /*if (x != n - 1) {
            ll p4 = (p[x] - p[0]) % (b[i] - p[0]);
            ll p5 = (p[x + 1] - p[x]) % (b[i] - p[x]);
            ll p6 = (p[0] - p[x + 1]) % (b[i] - p[x + 1]);
            if (p4 > 0 && p5 > 0 && p6 > 0) {
                cont = true;
            }
        }
        if (x >= 2) {
            ll p4 = (p[x - 2] - p[0]) % (b[i] - p[0]);
            ll p5 = (p[x - 1] - p[x - 2]) % (b[i] - p[x - 2]);
            ll p6 = (p[0] - p[x - 1]) % (b[i] - p[x - 1]);
            if (p4 > 0 && p5 > 0 && p6 > 0) {
                cont = true;
            }
        }*/
        /*if (!cont) {
            cout << "NO" << nl;
            return 0;
        }*/
    }
    cout << "YES" << nl;
}
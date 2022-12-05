#ifndef ONPC
#pragma GCC optimize("O3")
#pragma GCC target("avx2,avx,sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,lzcnt")
#pragma GCC optimize("unroll-loops")
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

struct Circle {
    Point p;
    ll r;
};

bool operator^(const Circle &a, const Circle &b) {
    return (a.p - b.p).abs2() < (a.r + b.r) * (a.r + b.r);
}

bool operator<(const Circle &a, const Circle &b) {
    return a.r > b.r;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Circle> v(n);
    for (auto& e : v)
        cin >> e.p.x >> e.p.y >> e.r;
    sort(all(v));
    vector<Circle> s1, s2;
    s1.reserve(n);
    s2.reserve(n);
    ll sum1 = 0, sum2 = 0;
    for (auto& c : v) {
        bool build1 = true, build2 = true;
        for (auto& c1 : s1) {
            if (c ^ c1)
                build1 = !build1;
        }
        for (auto& c2 : s2) {
            if (c ^ c2)
                build2 = !build2;
        }
        if (build1) {
            s1.push_back(c);
            sum1 += c.r * c.r;
        } else if (build2) {
            s2.push_back(c);
            sum2 += c.r * c.r;
        } else {
            s1.push_back(c);
            sum1 -= c.r * c.r;
        }
    }
    cout << fixed << setprecision(10);
    cout << 1.0l * (sum1 + sum2) * PI << nl;
}
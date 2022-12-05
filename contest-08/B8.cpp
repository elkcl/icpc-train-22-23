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
    vll v(n, 0);
    for (int i = 2; i < n; ++i) {
        cout << "1 1 2 " << i + 1 << nl;
        cin >> v[i];
    }
    vi left, right;
    left.reserve(n);
    right.reserve(n);
    for (int i = 2; i < n; ++i) {
        int s;
        cout << "2 1 2 " << i + 1 << nl;
        cin >> s;
        if (s > 0)
            left.push_back(i);
        else
            right.push_back(i);
    }
    int left_max = -1;
    int right_max = -1;
    if (!left.empty()) {
        left_max = left[0];
        for (auto e : left) {
            if (v[e] > v[left_max])
                left_max = e;
        }
        left.erase(find(all(left), left_max));
    }
    if (!right.empty()) {
        right_max = right[0];
        for (auto e : right) {
            if (v[e] > v[right_max])
                right_max = e;
        }
        right.erase(find(all(right), right_max));
    }
    vi left_left, left_right, right_left, right_right;
    for (auto e : left) {
        int s;
        cout << "2 1 " << left_max + 1 << ' ' << e + 1 << nl;
        cin >> s;
        if (s > 0)
            left_left.push_back(e);
        else
            left_right.push_back(e);
    }
    for (auto e : right) {
        int s;
        cout << "2 1 " << right_max + 1 << ' ' << e + 1 << nl;
        cin >> s;
        if (s > 0)
            right_left.push_back(e);
        else
            right_right.push_back(e);
    }
    auto cmp1 = [&v](int a, int b) -> bool {
        return v[a] < v[b];
    };
    auto cmp2 = [&v](int a, int b) -> bool {
        return v[a] > v[b];
    };
    sort(all(right_right), cmp1);
    sort(all(right_left), cmp2);
    sort(all(left_right), cmp1);
    sort(all(left_left), cmp2);

    cout << "0 1 ";
    if (right_max != -1) {
        for (auto e: right_right)
            cout << e + 1 << ' ';
        cout << right_max + 1 << ' ';
        for (auto e: right_left)
            cout << e + 1 << ' ';
    }
    cout << "2 ";
    if (left_max != -1) {
        for (auto e: left_right)
            cout << e + 1 << ' ';
        cout << left_max + 1 << ' ';
        for (auto e: left_left)
            cout << e + 1 << ' ';
    }
    cout << nl;
}
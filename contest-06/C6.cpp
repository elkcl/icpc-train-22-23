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

const int K = 5;

struct query {
    int l, r, k, id;
};

void solve(const vi &a, const vvi &cnt, vector<query> &&qs, vi &ans, int l, int r) {
    if (r - l == 0)
        return;
    if (r - l == 1) {
        for (auto& q : qs) {
            if (q.l == l && q.r == r) {
                ans[q.id] = a[l];
            }
        }
        return;
    }
    int m = (l + r) / 2;
    vector<vii> lp(m - l + 1, vii(K, {-1, -1})), rp(r - m + 1, vii(K, {-1, -1}));
    for (int i = 1; i < m - l + 1; ++i) {
        lp[i] = lp[i - 1];
        int curr = upper_bound(all(cnt[a[m - i]]), m - 1) - lower_bound(all(cnt[a[m - i]]), m - i);
        for (int j = 0; j < K; ++j) {
            if (a[m - i] == lp[i][j].first) {
                lp[i].erase(lp[i].begin() + j);
                break;
            }
        }
        for (int j = 0; j < lp[i].size(); ++j) {
            if (curr > lp[i][j].second) {
                lp[i].insert(lp[i].begin() + j, {a[m - i], curr});
                if (lp[i].size() > K)
                    lp[i].erase(lp[i].end() - 1);
                break;
            }
        }
        if (lp[i].size() < K)
            lp[i].emplace_back(a[m - i], curr);
    }
    for (int i = 1; i < r - m + 1; ++i) {
        rp[i] = rp[i - 1];
        int curr = upper_bound(all(cnt[a[m + i - 1]]), m + i - 1) - lower_bound(all(cnt[a[m + i - 1]]), m);
        for (int j = 0; j < K; ++j) {
            if (a[m + i - 1] == rp[i][j].first) {
                rp[i].erase(rp[i].begin() + j);
                break;
            }
        }
        for (int j = 0; j < rp[i].size(); ++j) {
            if (curr > rp[i][j].second) {
                rp[i].insert(rp[i].begin() + j, {a[m + i - 1], curr});
                if (rp[i].size() > K)
                    rp[i].erase(rp[i].end() - 1);
                break;
            }
        }
        if (rp[i].size() < K)
            rp[i].emplace_back(a[m + i - 1], curr);
    }
    vector<query> ql, qr;
    ql.reserve(qs.size());
    qr.reserve(qs.size());
    for (auto& q : qs) {
        if (l <= q.l && q.l < m && q.r <= m)
            ql.push_back(q);
        if (m <= q.l && q.l < r && q.r <= r)
            qr.push_back(q);
        if (l <= q.l && q.l <= m && m <= q.r && q.r <= r) {
            int cans = 1'000'000'000;
            for (auto &c : lp[m - q.l]) {
                if (c.first == -1)
                    continue;
                if ((upper_bound(all(cnt[c.first]), q.r - 1) - lower_bound(all(cnt[c.first]), q.l)) * q.k <= q.r - q.l)
                    continue;
                cans = min(cans, c.first);
            }
            for (auto &c : rp[q.r - m]) {
                if (c.first == -1)
                    continue;
                if ((upper_bound(all(cnt[c.first]), q.r - 1) - lower_bound(all(cnt[c.first]), q.l)) * q.k <= q.r - q.l)
                    continue;
                cans = min(cans, c.first);
            }
            if (cans == 1'000'000'000)
                ans[q.id] = -2;
            else
                ans[q.id] = cans;
        }
    }
    solve(a, cnt, move(ql), ans, l, m);
    solve(a, cnt, move(qr), ans, m, r);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vi a(n);
    for (auto &e : a) {
        cin >> e;
        --e;
    }
    vector<query> qs(q);
    for (int i = 0; i < q; ++i) {
        cin >> qs[i].l >> qs[i].r >> qs[i].k;
        --qs[i].l;
        qs[i].id = i;
    }
    vvi cnt(n);
    for (int i = 0; i < n; ++i) {
        cnt[a[i]].push_back(i);
    }
    vi ans(q);
    solve(a, cnt, move(qs), ans, 0, n);
    for (auto e : ans)
        cout << e + 1 << nl;
}
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3e5 + 10;
const int MAXQ = MAXN;

using ll = long long;
using pii = pair<int, int>;

struct Query {
    int l, r, k, ind;
};

vector<int> a(MAXN);
vector<int> ans(MAXQ, 0);
vector<int> pref[MAXN], suf[MAXN];


int32_t main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        suf[a[i]].push_back(i);
    }

    for (int i = n - 1; i >= 0; i--) {
        pref[a[i]].push_back(-i);
    }

    vector<Query> queries(q);

    map<int, int> cnt;
    for (auto& x : queries) {
        cin >> x.l >> x.r >> x.k;
        x.l--;

        for (int i = x.l; i < x.r; i++) {
            cnt[a[i]]++;
        }

        int ans = INT_MAX;
        for (auto [k, v] : cnt) {
            if (x.r - x.l < x.k * v) {
                ans = min(ans, k);
            }
        }

        cout << (ans == INT_MAX ? -1 : ans) << "\n";

        cnt.clear();
    }


    return 0;
}


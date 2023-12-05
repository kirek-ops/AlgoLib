/// task: https://codeforces.com/gym/102962/problem/E
/// time complexity: O((q + n)log(n)) 

#include <bits/stdc++.h>
#define fr first
#define sc second
#define all(x) (x).begin(), (x).end()
#define pw(x) (1ll << x)
#define pb push_back
#define endl '\n'
#define sz(x) (int)((x).size())
#define vec vector

using namespace std;

template <typename T> inline bool umin (T &a, const T &b) { if (a > b) { a = b; return 1; } return 0; }
template <typename T> inline bool umax (T &a, const T &b) { if (a < b) { a = b; return 1; } return 0; }

typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;
typedef pair <int, int> pii;

const int N = 6e5 + 10;

struct dsu {
    vec <int> p, rk;
    vec <array <int, 6>> his;
    dsu (int n = 0) : p(n), rk(n, 1) { iota(all(p), 0); }
    inline int par (int x) { while (x ^ p[x]) x = p[x]; return x; }
    inline bool unite (int x, int y) {
        x = par(x), y = par(y);
        if (x == y) return 0;
        if (rk[x] < rk[y]) swap(x, y);
        his.pb({x, y, p[x], p[y], rk[x], rk[y]});
        rk[x] += rk[y]; p[y] = x; return 1;
    }
    inline int now () { return sz(his); }
    inline void roll (int to) {
        while (sz(his) != to) {
            auto [x, y, px, py, rkx, rky] = his.back(); his.pop_back();
            p[x] = px; p[y] = py;
            rk[x] = rkx; rk[y] = rky;
        }
    }
};

int orz[N];
vec <array <int, 3>> ed;
vec <pii> qry;
dsu D (N);

inline void func (int l, int r, vec <int> id, vec <int> &must, vec <int> &maybe) {
    sort(all(id), [&] (int i, int j) { return ed[i][2] < ed[j][2]; });
    int wow = D.now();
    for (int i = l; i <= r; ++i) {
        auto [u, v, w] = ed[qry[i].fr];
        D.unite(u, v);
    }
    for (auto &i : id) {
        auto [u, v, w] = ed[i];
        if (D.unite(u, v)) must.pb(i);
    }
    D.roll(wow);
    for (auto &i : must) {
        auto [u, v, w] = ed[i];
        D.unite(u, v);
    }
    for (auto &i : id) {
        auto [u, v, w] = ed[i];
        if (D.unite(u, v)) maybe.pb(i);
    }
    D.roll(wow);
}

inline void rec (int l, int r, vec <int> cnst, ll cv) {
    if (l == r) {
        auto [id, wi] = qry[l]; ed[id][2] = wi;
        ll mn = wi;
        for (auto &i : cnst) umin(mn, (ll)ed[i][2]);
        cout << mn + cv << endl;
        return;
    }
    int mid = (l + r) >> 1;
    vec <int> lef = cnst, rig = cnst;
    vec <int> must, maybe;
    for (int i = mid + 1; i <= r; ++i) {
        auto [id, wi] = qry[i];
        --orz[id];
        if (!orz[id]) lef.pb(id);
    }
    func(l, mid, lef, must, maybe);
    int wow = D.now();
    ll lcv = cv;
    for (auto &i : must) {
        auto [u, v, w] = ed[i];
        lcv += w; D.unite(u, v);
    }
    rec(l, mid, maybe, lcv);
    D.roll(wow);

    must.clear(); maybe.clear();
    for (int i = mid + 1; i <= r; ++i) {
        auto [id, wi] = qry[i];
        ++orz[id];
    }

    for (int i = l; i <= mid; ++i) {
        auto [id, wi] = qry[i];
        --orz[id];
        if (!orz[id]) rig.pb(id);
    }
    wow = D.now();
    func(mid + 1, r, rig, must, maybe);
    ll rcv = cv;
    for (auto &i : must) {
        auto [u, v, w] = ed[i];
        rcv += w; D.unite(u, v);
    }
    rec(mid + 1, r, maybe, rcv);
    D.roll(wow);
    for (int i = l; i <= mid; ++i) {
        auto [id, wi] = qry[i];
        ++orz[id];
    }
}

inline void solve () {
    int n, m; cin >> n >> m; ed.reserve(n + m);

    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        ed.pb({0, i + 1, x});
    }
    for (int i = 0; i < m; ++i) {
        int u, v, x; cin >> u >> v >> x;
        ed.pb({u, v, x});
    }

    int q; cin >> q; qry.reserve(q);
    for (int i = 0; i < q; ++i) {
        int id, w; cin >> id >> w; --id;
        qry.pb({id, w});
        ++orz[id];
    }

    vec <int> cnst; cnst.reserve(n + m);
    for (int i = 0; i < sz(ed); ++i) if (!orz[i]) cnst.pb(i);

    rec(0, q - 1, cnst, 0);
}

signed main () {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif// LOCAL
    int t = 1; //cin >> t;
    while (t--) solve();
    return 0;
}

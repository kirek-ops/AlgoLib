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

struct fenwick {
    vector <int> t;
    fenwick () {}
    fenwick (int n) : t (n + 100) {}
    inline void upd (int p, int x) { for (p += 5; p < sz(t); p += (p & (-p))) t[p] += x; }
    inline int get (int p) { int res = 0; for (p += 5; p; p -= (p & (-p))) res += t[p]; return res; }
    inline int get (int l, int r) { return get(r) - get(l - 1); }
};

inline void solve () {
    int n, q; cin >> n >> q;
    fenwick st (n);
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int i, x; cin >> i >> x;
            st.upd(i, x);
        }
        else {
            int l, r; cin >> l >> r;
            cout << st.get(l, r) << endl;
        }
    }
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

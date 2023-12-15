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

const int MX = (int)1e9 + 100;
const ll INF = (ll)1e18 + 100;
const int N = (int)3e5 + 10;

struct line {
    ll k, b;
    line () : k(0), b(-INF) {}
    line (ll k, ll b) : k(k), b(b) {}
    inline ll operator () (const ll &x) {
        return x * k + b;
    }
};

struct node {
    node *l, *r;
    line bst;
    node () : l(nullptr), r(nullptr) {}
};

struct lichao {
    node *root = new node ();
    inline node *add (node *v, ll tl, ll tr, line x) {
        if (!v) {
            v = new node (); v->bst = x;
            return v;
        }
        ll tm = (tl + tr) >> 1;
        bool lef = x(tl) > v->bst(tl);
        bool mid = x(tm) > v->bst(tm);
        if (mid) swap(x, v->bst);   
        if (tl == tr) return v;
        if (lef != mid) v->l = add(v->l, tl, tm, x);
        else v->r = add(v->r, tm + 1, tr, x);
        return v;
    }
    inline ll get (node *v, ll tl, ll tr, ll x) {
        if (!v) return -INF;
        ll y = v->bst(x);
        if (tl == tr) return y;
        ll tm = (tl + tr) >> 1;
        if (x <= tm) umax(y, get(v->l, tl, tm, x));
        else umax(y, get(v->r, tm + 1, tr, x));
        return y;
    }

    inline void clean (node *v) {
        if (!v) return;
        clean(v->l); clean(v->r);
        delete v;
    }

    inline void add (line x) {
        add(root, -MX, MX, x);
    }
    inline ll get (ll x) {
        return get(root, -MX, MX, x);
    }
    inline void clean () { 
        clean(root); root = new node ();
    }
};

inline void solve () {
    int q; cin >> q;
    lichao st;
    while (q--) {
        int type; cin >> type; 
        if (type == 1) { // add new line
            ll k, b; cin >> k >> b;
            st.add(line(k, b));
        }
        else { // get best in point x
            ll x; cin >> x;
            cout << st.get(x) << endl;
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

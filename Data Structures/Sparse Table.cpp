#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define fr first
#define sc second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pw(x) (1ll << x)
#define sz(x) (int)((x).size())
#define pb push_back
#define endl '\n'
#define mp make_pair
#define vec vector
 
using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef long double ld;
typedef pair <int, int> pii;
typedef pair <ll, ll> pll;
typedef unsigned long long ull;
 
template <typename T> inline bool umin (T &a, const T &b) { if (a > b) { a = b; return 1; } return 0; }
template <typename T> inline bool umax (T &a, const T &b) { if (a < b) { a = b; return 1; } return 0; }
template <typename T>
using oset = tree<T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;
 
const int N = 2e6;
int _log[N];

struct sparse {
    vector <vector <int>> st;
    sparse (const vector <int> &a) {
        int n = sz(a);
        st = vector <vector <int>> (n, vector <int> (_log[n] + 1));
        for (int i = 0; i < n; ++i) st[i][0] = a[i];
        for (int j = 1; j <= _log[n]; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    inline int get (int l, int r) {
        int j = _log[r - l + 1];
        return min(st[l][j], st[r - (1 << j) + 1][j]);
    }
};  
 
inline void solve () {
    int n; cin >> n;
    vector <int> a (n);
    for (auto &i : a) cin >> i;
    sparse st (a);
    int q; cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;
        cout << st.get(l, r) << endl;
    }
}
 
signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    _log[1] = 0;
    for (int i = 2; i < N; ++i) _log[i] = _log[i >> 1] + 1;
    int t = 1; // cin >> t;
    while (t--) solve();
    return 0;
}

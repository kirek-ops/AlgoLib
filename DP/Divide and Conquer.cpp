/*
task: https://oj.uz/problem/view/APIO14_sequence
*/
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
 
const ll inf = 1e18 + 527;
const int N = 1e5 + 100;
const int K = 205;
 
ll a[N], p[N], dp[N][2];
int par[N][K];
ll sum = 0;
 
inline ll cost (int l, int r) { return (sum - p[r]) * (p[r] - p[l - 1]); }
inline void dc (int l, int r, int optl, int optr, int lay) {
    if (l > r) return;
    int mid = (l + r) >> 1;
    pair <ll, int> opt = {-inf, -1};
    int play = (lay & 1) ^ 1;
    for (int i = optl; i <= min(mid, optr); ++i) umax(opt, mp(dp[i - 1][play] + cost(i, mid), i));
    dp[mid][lay & 1] = opt.fr;
    par[mid][lay] = opt.sc - 1;
    dc(l, mid - 1, optl, opt.sc, lay);
    dc(mid + 1, r, opt.sc, optr, lay);
};
 
inline void solve () {
    int n, k; cin >> n >> k; ++k;
    for (int i = 1; i <= n; ++i) cin >> a[i], sum += a[i];
    for (int i = 1; i <= n; ++i) p[i] = p[i - 1] + a[i];

    for (int i = 1; i <= n; ++i) dp[i][1] = cost(1, i);
    for (int i = 2; i <= k; ++i) {
        int lay = i & 1;
        int nlay = lay ^ 1;
        dc(i, n, 1, n, i);
    }
    vector <int> res;
    cout << dp[n][k & 1] << endl;
    int id = n;
    for (int i = k; i >= 2; --i) {
        id = par[id][i];
        cout << id << " ";
    }
}
 
signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int t = 1; // cin >> t;
    while (t--) solve();
    return 0;
}

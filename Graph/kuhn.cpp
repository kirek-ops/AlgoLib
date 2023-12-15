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

const int N = 1e4 + 10;

vector <int> g[N];
int mt[N], used[N];

inline bool kuhn (int v) {
    if (used[v]) return false;
    used[v] = 1;
    for (const auto &u : g[v]) if (!~mt[u]) { mt[u] = v; return true; }
    for (const auto &u : g[v]) if (kuhn(mt[u])) { mt[u] = v; return true; }
    return false;
}

inline void solve () {
    int n, k, m; cin >> n >> k >> m;
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v); g[v].pb(u);
    }

    fill(mt, mt + k, -1);
    for (int i = 0; i < n; ++i) {
        fill(used, used + n, 0);
        kuhn(i);
    }

    for (int i = 0; i < k; ++i) {
        if (~mt[i]) {
            cout << mt[i] + 1 << " <-> " << i << endl;
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

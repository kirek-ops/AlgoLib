/*
task: https://codeforces.com/gym/100140 (H)
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define fr first
#define sc second
#define all(x) (x).begin(), (x).end()
#define pw(x) (1ll << x)
#define sz(x) (int)((x).size())
#define pb push_back
#define endl '\n'

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef long double ld;
typedef pair <int, int> pii;
typedef pair <ll, ll> pll;

template <typename T> inline bool umin (T &a, const T &b) { if (a > b) { a = b; return 1; } return 0; }
template <typename T> inline bool umax (T &a, const T &b) { if (a < b) { a = b; return 1; } return 0; }
template <typename T>
using oset = tree<T, null_type, less_equal <T>, rb_tree_tag, tree_order_statistics_node_update>;

const int N = 500;

struct MCMF {
    struct edge {
        int to, cap, cost, flow, rev;
        edge () {}
        edge (int to, int cap, int cost, int flow, int rev) : to(to), cap(cap), cost(cost), flow(flow), rev(rev) {}
    };

    vector <edge> g[N];
    int q[N], d[N];
    pii par[N];

    inline void add (int u, int v, int cap, int cost) {
        g[u].pb(edge(v, cap,  cost, 0, sz(g[v])    ));
        g[v].pb(edge(u,   0, -cost, 0, sz(g[u]) - 1));
    }

    inline void levit (int s) {
        vector <int> id (N);
        fill(d, d + N, 1e9);
        int ukh = 0, ukt = 1;
        q[0] = s; d[s] = 0;
        while (ukh != ukt) {
            int v = q[ukh++];
            id[v] = 2;
            if (ukh == N) ukh = 0;
            for (int i = 0; i < sz(g[v]); ++i) {
                auto &[to, cap, cost, flow, rev] = g[v][i];
                if (cap > flow && d[to] > d[v] + cost) {
                    d[to] = d[v] + cost;
                    if (!id[to]) {
                        q[ukt++] = to;
                        if (ukt == N) ukt = 0;
                    }
                    else if (id[to] == 2) {
                        if (--ukh == -1) ukh = N - 1;
                        q[ukh] = to;
                    }
                    id[to] = 1;
                    par[to] = {v, i};
                }
            }
        }
    }

    inline pii mcf (int k, int s, int f) { /// find min cost flow k 
        int cost = 0, FLOW = 0;
        while (k > 0) {
            levit(s);
            if (d[f] == 1e9) break;
            int go = f, flow = 1e9;
            while (go != s) {
                auto &[u, id] = par[go];
                umin(flow, g[u][id].cap - g[u][id].flow);
                go = u;
            }
            umin(flow, k); k -= flow; FLOW += flow; go = f;
            while (go != s) {
                auto &[u, id] = par[go];
                cost += g[u][id].cost * flow;
                g[u][id].flow += flow;
                g[go][g[u][id].rev].flow -= flow;
                go = u;
            }
        }
        return {FLOW, cost};
    }
};

inline void solve () {
    int n, k; cin >> n >> k;
    vector <pii> a (n);
    vector <vector <int>> b (k);

    const int S = 0, F = n + k + 1;
    MCMF st;

    /// network
    for (int i = 1; i <= k; ++i) st.add(S, i, 1, 0);
    for (int i = 1; i <= n; ++i) {
        int s, c; cin >> s >> c;
        st.add(k + i, F, s, c);
    }
    for (int i = 1; i <= k; ++i) {
        int T; cin >> T;
        while (T--) {
            int x; cin >> x; x += k;
            st.add(i, x, 1, 0);
        }
    }
    auto x = st.mcf(k, S, F);
    if (x.fr != k) cout << -1 << endl;
    else cout << x.sc << endl;
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t = 1; // cin >> t;
    while (t--) solve();
    return 0;
}

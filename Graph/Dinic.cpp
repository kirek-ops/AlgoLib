/*
task: https://codeforces.com/gym/100140 (A)
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

const int N = 10000;

struct Dinic {
    struct edge {
        int u, v, cap, flow;
        edge () {}
        edge (int u, int v, int cap, int flow) : u(u), v(v), cap(cap), flow(flow) {}
    };

    vector <int> g[N];
    vector <edge> ed;
    const int inf = 1e9;
    int d[N], uk[N], S, F;

    Dinic () : S(0), F(N - 1) {}
    Dinic (int S, int F) : S(S), F(F) {}

    inline void add (int u, int v, int cap) {
        edge e (u, v, cap, 0), ee (v, u, 0, 0);
        g[u].pb(sz(ed));
        g[v].pb(sz(ed) + 1);
        ed.pb(e); ed.pb(ee);
    }

    inline bool bfs () {
        fill(d, d + N, -1); d[S] = 0;
        queue <int> q; q.push(S);
        while (sz(q)) {
            int v = q.front(); q.pop();
            for (auto id : g[v]) {
                auto &[_, to, cap, flow] = ed[id];
                if (cap > flow && !~d[to]) {
                    q.push(to);
                    d[to] = d[v] + 1;
                }
            }
        }
        return (~d[F]);
    }

    inline int dfs (int v, int flow) {
        if (!flow) return 0;
        if (v == F) return flow;
        for (; uk[v] < sz(g[v]); ++uk[v]) {
            auto &[_, to, cap, flw] = ed[g[v][uk[v]]];
            if (d[v] + 1 != d[to]) continue;
            int pushed = dfs(to, min(flow, cap - flw));
            if (pushed) {
                ed[g[v][uk[v]]].flow += pushed;
                ed[g[v][uk[v]] ^ 1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

    inline int flow () {
        int res = 0;
        while (bfs()) {
            fill(uk, uk + N, 0);
            while (int push = dfs(S, inf)) res += push;
        }
        return res;
    }
};

inline void solve () {
        int n, m; cin >> n >> m;
        Dinic d (0, 2 * n - 1);
        
        for (int i = 1; i <= n; ++i) d.add(d.S, i, 1);
        for (int i = 0; i < m; ++i) {
            int u, v; cin >> u >> v;
            d.add(u, v + n, 1);
        }
        for (int i = 1; i <= n; ++i) d.add(i + n, d.F, 1);
        cout << n - d.flow() << endl;
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t = 1; // cin >> t;
    while (t--) solve();
    return 0;
}

/*
task: https://codeforces.com/gym/100140 (A)
*/
#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define endl '\n'
#define sz(x) (int)((x).size())

using namespace std;

struct MPM {
    struct edge {
        int v, u;
        long long cap, flow;
        edge () {}
        edge (int v, int u, long long cap, long long flow) : v(v), u(u), cap(cap), flow(flow) {}
        edge (int v, int u, long long cap) : v(v), u(u), cap(cap), flow(0ll) {}
    };
    const long long flow_inf = 1e18;
    vector <edge> edges;
    vector <char> alive;
    vector <long long> pin, pout;
    vector <list <int>> in, out;
    vector <vector <int>> adj;
    vector <long long> ex;
    int n, m = 0;
    int s, t;
    vector <int> level;
    vector <int> q;
    int qh, qt;
    inline void create (int _n) {
        n = _n;
        ex.resize(n); q.resize(n);
        pin.resize(n); pout.resize(n);
        adj.resize(n); level.resize(n);
        in.resize(n); out.resize(n);
    }
    MPM () {}
    MPM (int n, int s, int t) : s(s), t(t) { create(n); }
    inline void add_edge (int v, int u, long long cap) {
        edges.pb(edge(v, u, cap));
        edges.pb(edge(u, v, 0));
        adj[v].pb(m);
        adj[u].pb(m + 1);
        m += 2;
    }
    inline bool bfs () {
        while (qh < qt){
            int v = q[qh++];
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1) continue;
                if (level[edges[id].u] != -1) continue;
                    level[edges[id].u] = level[v] + 1;
                    q[qt++] = edges[id].u;
                }
            }
            return level[t] != -1;
        }
        inline long long pot (int v) { return min(pin[v], pout[v]); }
        inline void remove_node(int v) {
            for (int i : in[v]) {
                int u = edges[i].v;
                auto it = find(out[u].begin(), out[u].end(), i);
                out[u].erase(it);
                pout[u] -= edges[i].cap - edges[i].flow;
            }
            for (int i : out[v]) {
                int u = edges[i].u;
                auto it = find(in[u].begin(), in[u].end(), i);
                in[u].erase(it);
                pin[u] -= edges[i].cap - edges[i].flow;
            }
        }
    inline void push (int from, int to, long long f, bool forw) {
        qh = 0; qt = 1; ex.assign(n, 0); ex[from] = f;
        q[0] = from;
        while (qh < qt) {
            int v = q[qh++];
            if (v == to) break;
            long long must = ex[v];
            auto it = forw ? out[v].begin() : in[v].begin();
            while (true) {
                int u = forw ? edges[*it].u : edges[*it].v;
                long long pushed = min(must, edges[*it].cap - edges[*it].flow);
                if (pushed == 0) break;
                if (forw) {
                    pout[v] -= pushed;
                    pin[u] -= pushed;
                }
                else {
                    pin[v] -= pushed;
                    pout[u] -= pushed;
                }
                if (ex[u] == 0) q[qt++] = u;
                ex[u] += pushed;
                edges[*it].flow += pushed;
                edges[(*it)^1].flow -= pushed;
                must -= pushed;
                if (edges[*it].cap - edges[*it].flow == 0) {
                    auto jt = it;
                    ++jt;
                    if (forw) {
                        in[u].erase(find(in[u].begin(), in[u].end(), *it));
                        out[v].erase(it);
                    }
                    else {
                        out[u].erase(find(out[u].begin(), out[u].end(), *it));
                        in[v].erase(it);
                    }
                    it = jt;
                }
                else break;
                if (!must) break;
            }
        }
    }
    inline long long flow() {
        long long ans = 0;
        while (true) {
            pin.assign(n, 0); pout.assign(n, 0);
            level.assign(n, -1); alive.assign(n, 1);
            level[s] = 0;
            qh = 0; qt = 1; q[0] = s;
            if (!bfs()) break;
            for (int i = 0; i < n; ++i){
                out[i].clear();
                in[i].clear();
            }
            for (int i = 0; i < m; ++i){
                if (edges[i].cap - edges[i].flow == 0) continue;
                int v = edges[i].v, u = edges[i].u;
                if (level[v] + 1 == level[u] && (level[u] < level[t] || u == t)) {
                    in[u].pb(i); out[v].pb(i);
                    pin[u] += edges[i].cap - edges[i].flow;
                    pout[v] += edges[i].cap - edges[i].flow;
                }
            }
            pin[s] = pout[t] = flow_inf;
            while (true) {
                int v = -1;
                for (int i = 0; i < n; ++i) {
                    if (!alive[i]) continue;
                    if (!~v || pot(i) < pot(v)) v = i;
                }
                if (!~v) break;
                if (!pot(v)) {
                    alive[v] = false;
                    remove_node(v);
                    continue;
                }
                long long f = pot(v); ans += f;
                push(v, s, f, 0); push(v, t, f, 1);
                alive[v] = false; remove_node(v);
            }
        }
        return ans;
    }
};

inline void solve () {
    int n, m; cin >> n >> m;
    MPM f (n + 2, 1, n);
    for (int i = 0; i < m; ++i) {
        int u, v, c; cin >> u >> v >> c;
        f.add_edge(u, v, c); f.add_edge(v, u, c);
    }
    cout << f.flow();
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

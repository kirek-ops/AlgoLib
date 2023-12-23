#include <bits/stdc++.h>

using namespace std;

vector <int> zfunc (const string &s) {
    int n = s.size();
    vector <int> z (n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

inline void solve () {
    string s; cin >> s;
    auto zf = zfunc(s);
    for (const auto &i : zf) cout << i << " ";
}

signed main () {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1; // cin >> t;
    while (t--) solve();
    return 0;
}
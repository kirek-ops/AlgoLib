#include <bits/stdc++.h>

using namespace std;

vector <int> pfunc (const string &s) {
    int n = s.size();
    vector <int> pf (n);
    for (int i = 1; i < n; ++i) {
        int j = pf[i - 1];
        while (j > 0 && s[i] != s[j]) j = pf[j - 1];
        if (s[i] == s[j]) ++j;
        pf[i] = j;
    }
    return pf;
}

inline void solve () {
    string s; cin >> s;
    auto p = pfunc(s);
    for (const auto &i : p) cout << i << " ";
}

signed main () {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1; // cin >> t;
    while (t--) solve();
    return 0;
}
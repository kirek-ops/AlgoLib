#include <bits/stdc++.h>
#include "Data Structures/Fenwick.hpp"

using namespace std;

struct comb {
    int operator () (const int &a, const int &b) const {
        return a + b;
    }
};

struct inv {
    int operator () (const int &a) const {
        return -a;
    }
};

int main () {
    ios_base::sync_with_stdio(0); cin.tie(0);

    Fenwick <int, comb, inv> fenwick (10);
    vector <int> tester (10);

    int q = 100;
    while (q--) {
        int id = rand() % 10;
        int val = rand() % 100;
        tester[id] += val;
        fenwick.upd(id, val);

        for (int i = 0; i < 10; i++) {
            int expected_sum = accumulate(tester.begin(), tester.begin() + i + 1, 0);
            assert(expected_sum == fenwick.get(0, i));
        }
    }


    cout << "All is good!";
    return 0;
}
#include <limits>
#include <iostream>

template <typename T>
inline bool umax (T &a, const T &b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

template <typename T>
inline bool umin (T &a, const T &b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

template <typename T>
struct line {
    T k, b;
    line () : k(0), b(std::numeric_limits<T>::lowest()) {}
    line (T k, T b) : k(k), b(b) {}
    inline T operator () (const T &x) {
        return x * k + b;
    }
};

template <typename T>
struct node {
    node *l, *r;
    line <T> bst;
    node () : l(nullptr), r(nullptr) {}
};

template <typename T>
class LiChao {
private:
    T LEFT, RIGHT;
    node <T> *root = new node <T> ();

    node <T> *add (node <T> *v, T tl, T tr, line <T> x) {
        if (!v) return new node <T> ({nullptr, nullptr, x});
        T tm = (tl + tr) >> 1;
        bool lef = x(tl) > v->bst(tl);
        bool mid = x(tm) > v->bst(tm);

        if (mid) std::swap(x, v->bst);
        if (tl == tr) return v;

        if (lef != mid) {
            v->l = add(v->l, tl, tm, x);
        }
        else {
            v->r = add(v->r, tm + 1, tr, x);
        }
        return v;
    }

    T get (node <T> *v, T tl, T tr, T x) {
        if (!v) return std::numeric_limits<T>::lowest();
        T y = v->bst(x);
        if (tl == tr) return y;
        T tm = (tl + tr) >> 1;

        if (x <= tm) {
            umax(y, get(v->l, tl, tm, x));
        }
        else {
            umax(y, get(v->r, tm + 1, tr, x));
        }
        return y;
    }

    void clean (node <T> *v) {
        if (!v) return;
        clean(v->l); clean(v->r);
        delete v;
    }
public:
    LiChao () = default;
    LiChao (T LEFT, T RIGHT) : LEFT(LEFT), RIGHT(RIGHT) {}

    inline void add (line <T> x) {
        add(root, LEFT, RIGHT, x);
    }
    inline T get (T x) {
        return get(root, LEFT, RIGHT, x);
    }
    inline void clean () {
        clean(root); root = new node <T> ();
    }
};

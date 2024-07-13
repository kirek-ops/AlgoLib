#include <vector>

template <typename T, typename Combine = std::plus<T>, typename Inverse = std::negate<T>>
class Fenwick {
private:
    int n;
    std::vector<T> t;
    Combine combine;
    Inverse inverse;

public:
    Fenwick(int n) : n(n), t(n + 1), combine(Combine()), inverse(Inverse()) {}

    inline void upd(int i, T val) {
        for (++i; i <= n; i += i & -i) {
            t[i] = combine(t[i], val);
        }
    }

    inline T operator[](int i) const {
        return get(i);
    }

    inline T get(int i) const {
        T res = T();
        for (++i; i > 0; i -= i & -i) {
            res = combine(res, t[i]);
        }
        return res;
    }

    inline T get(int l, int r) const {
        if (l > 0) {
            return combine(get(r), inverse(get(l - 1)));
        } else {
            return get(r);
        }
    }
};

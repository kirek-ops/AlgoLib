#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

class BigInt {
        private:
                static const int base = 1e9;
                static const int ss = 9;
                vector <int> dig;
                int sign = 1;
        public:
                BigInt () : dig(1, 0), sign(1) {}
                BigInt (const int &sign, const vector <int> &dig) : sign(sign), dig(dig) {}
                BigInt (const string &s) {
                        int sh = 0;
                        if (s[0] == '-') sh = 1, sign = -1;
                        for (int i = (int)s.size() - ss; i >= sh; i -= ss) {
                                dig.push_back(stoi(s.substr(i, ss)));
                        }
                        if (((int)s.size() - sh) % ss) {
                                dig.push_back(stoi(s.substr(sh, ((int)s.size() - sh) % ss)));
                        }
                }

                void norm ();

                BigInt & operator = (const BigInt &other);
                friend istream & operator >> (istream &in, BigInt &x);
                friend ostream & operator << (ostream &out, const BigInt &x);

                bool operator < (const BigInt &other) const;
                bool operator > (const BigInt &other) const;
                bool operator == (const BigInt &other) const;
                bool operator != (const BigInt &other) const;
                bool operator <= (const BigInt &other) const;
                bool operator >= (const BigInt &other) const;

                BigInt operator - () const;

                BigInt operator + (const BigInt &other) const;
                BigInt operator - (const BigInt &other) const;
                BigInt operator * (const BigInt &other) const;

                BigInt operator + (const int &x) const;
                BigInt operator - (const int &x) const;

                BigInt & operator += (const BigInt &other);
                BigInt & operator -= (const BigInt &other);
                BigInt & operator *= (const BigInt &other);

                BigInt & operator += (const int &x);
                BigInt & operator -= (const int &x);

                BigInt operator * (int x) const;
                BigInt operator / (int x) const;
                int operator % (const int &x) const;

                BigInt & operator *= (const int &x);
                BigInt & operator /= (const int &x);
                BigInt & operator %= (const int &x);

                BigInt & operator ++ ();
};

void BigInt::norm () {
        while (!dig.empty() && !dig.back()) dig.pop_back();
        if (dig.empty()) dig.push_back(0), sign = 1;
}
BigInt & BigInt::operator = (const BigInt &other) {
        dig = other.dig;
        sign = other.sign;
        return *this;
}
istream & operator >> (istream &in, BigInt &x) {
        string s; in >> s;
        x = BigInt(s);
        return in;
}
ostream & operator << (ostream &out, const BigInt &x) {
        if (!~x.sign) out << "-";
        char filler = out.fill('0');
        cout << x.dig.back();
        for (int i = (int)x.dig.size() - 2; i >= 0; --i) {
                out << setw(x.ss) << x.dig[i];
        }
        return out;
}
bool BigInt::operator < (const BigInt &other) const {
        if (sign < other.sign) return 1;
        if (sign > other.sign) return 0;
        if (sign == -1) {
                if (dig.size() < other.dig.size()) return 0;
                else if (dig.size() > other.dig.size()) return 1;
                else {
                        for (int i = dig.size() - 1; i >= 0; --i) {
                                if (dig[i] < other.dig[i]) return 0;
                                if (dig[i] > other.dig[i]) return 1;
                        }
                }
        }
        else {
                if (dig.size() < other.dig.size()) return 1;
                else if (dig.size() > other.dig.size()) return 0;
                else {
                        for (int i = dig.size() - 1; i >= 0; --i) {
                                if (dig[i] < other.dig[i]) return 1;
                                if (dig[i] > other.dig[i]) return 0;
                        }
                }
        }
        return 0;
}
bool BigInt::operator > (const BigInt &other) const {
        return !(*this <= other);
}
bool BigInt::operator == (const BigInt &other) const {
        if (sign != other.sign) return 0;
        if (dig.size() != other.dig.size()) return 0;
        for (int i = 0; i < dig.size(); ++i) if (dig[i] != other.dig[i]) return 0;
        return 1;
}
bool BigInt::operator != (const BigInt &other) const {
        return !(*this == other);
}
bool BigInt::operator <= (const BigInt &other) const {
        return (*this < other || *this == other);
}
bool BigInt::operator >= (const BigInt &other) const {
        return (*this > other || *this == other);
}
BigInt BigInt::operator - () const {
        BigInt tm = *this;
        tm.sign = -tm.sign;
        return tm;
}

BigInt BigInt::operator + (const BigInt &other) const {
        if (sign == 1 && other.sign == 1) {
                int buf = 0;
                BigInt res = (*this);
                for (int i = 0; i < other.dig.size() || buf > 0; ++i) {
                        if (i == res.dig.size()) res.dig.push_back(0);
                        res.dig[i] += buf + (i < other.dig.size() ? other.dig[i] : 0);
                        buf = res.dig[i] / base;
                        res.dig[i] %= base;
                }
                res.norm();
                return res;
        }
        else if (sign == 1 && other.sign == -1) return (*this - (-other));
        else if (sign == -1 && other.sign == -1) return -(-(*this) + (-other));
        else if (sign == -1 && other.sign == 1) return -(-(*this) - other);
        return BigInt();
}
BigInt BigInt::operator - (const BigInt &other) const {
        if (sign == 1 && other.sign == 1) {
                if ((*this) < other) return -(other - (*this));
                else {
                        BigInt res = *this;
                        int buf = 0;
                        for (int i = 0; i < other.dig.size() || buf > 0; ++i) {
                                res.dig[i] -= buf + (i < other.dig.size() ? other.dig[i] : 0);
                                if (res.dig[i] < 0) {
                                        buf = 1; res.dig[i] += base;
                                }
                                else buf = 0;
                        }
                        res.norm();
                        return res;
                }
        }
        else if (sign == 1 && other.sign == -1) return ((*this) + (-other));
        else if (sign == -1 && other.sign == -1) return -(-(*this) - (-other));
        else if (sign == -1 && other.sign == 1) return -(-(*this) + other);
        return BigInt();
}
BigInt BigInt::operator * (const BigInt &other) const {
        BigInt res;
        res.sign = sign * other.sign;
        res.dig.resize(dig.size() + other.dig.size());
        for (int i = 0; i < dig.size(); ++i) {
                if (!dig[i]) continue;
                int buf = 0;
                for (int j = 0; j < other.dig.size() || buf; ++j) {
                        long long ml = res.dig[i + j] + buf + dig[i] * 1ll * (j < other.dig.size() ? other.dig[j] : 0);
                        res.dig[i + j] = ml % base;
                        buf = ml / base;
                }
        }
        res.norm();
        return res;
}

BigInt BigInt::operator + (const int &x) const {
        return (*this) + BigInt(to_string(x));
}
BigInt BigInt::operator - (const int &x) const {
        return (*this) + (-x);
}

BigInt & BigInt::operator += (const BigInt &other) {
        *this = *this + other;
        return *this;
}
BigInt & BigInt::operator -= (const BigInt &other) {
        *this = *this - other;
        return *this;
}
BigInt & BigInt::operator *= (const BigInt &other) {
        (*this) = (*this) * other;
        return *this;
}

BigInt BigInt::operator * (int x) const {
        BigInt res = (*this);
        res.sign *= (x < 0 ? -1 : 1);
        x *= (x < 0 ? -1 : 1);
        int buf = 0;
        for (int i = 0; i < res.dig.size() || buf > 0; ++i) {
                if (i == res.dig.size()) res.dig.push_back(0);
                long long ml = buf + res.dig[i] * 1ll * x;
                res.dig[i] = ml % base;
                buf = ml / base;
        }
        res.norm();
        return res;
}
BigInt BigInt::operator / (int x) const {
        vector <int> d = this -> dig;
        reverse(d.begin(), d.end());
        BigInt res;
        res.sign = ((this -> sign) * (x < 0 ? -1 : 1));
        x = abs(x);
        long long s = 0, uk = 0;
        while (uk < d.size() && s < x) {
                s *= (this -> base); s += d[uk++];
        }
        while (uk < d.size()) {
                res.dig.push_back(s / x);
                s %= x; s *= (this -> base); s += d[uk++];
        }
        res.dig.push_back(s / x);
        reverse(res.dig.begin(), res.dig.end()); res.norm();
        return res;
}
int BigInt::operator % (const int &x) const {
        vector <int> d = this -> dig;
        reverse(d.begin(), d.end());
        long long s = 0, uk = 0;
        while (uk < d.size() && s < x) {
                s *= (this -> base); s += d[uk++];
        }
        while (uk < d.size()) {
                s %= x; s *= (this -> base); s += d[uk++];
        }
        s %= x;
        if (!~sign) s = (x - s);
        return s;
}

BigInt & BigInt::operator *= (const int &x) {
        (*this) = (*this) * x;
        return *this;
}
BigInt & BigInt::operator /= (const int &x) {
        (*this) = (*this) / x;
        return *this;
}
BigInt & BigInt::operator %= (const int &x) {
        (*this) = BigInt(to_string((*this) % x));
        return *this;
}

BigInt & BigInt::operator ++ () {
        (*this) = (*this) + 1;
        return (*this);
}
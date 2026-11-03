#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;


struct BigNum {
    static constexpr int BASE = 1000000000;
    static constexpr int BASE_DIGITS = 9;
    // Little-endian: a[0] is the least significant block.
    vector<int> a;
    int sign; // +1 or -1; zero always has sign +1.
    BigNum() : a(1, 0), sign(1) {}
    BigNum(ll value) : sign(1) {
        unsigned long long x;
        if (value < 0) {
            sign = -1;
            x = 0ULL - (unsigned long long)value;
        } else {
            x = (unsigned long long)value;
        }
        a.clear();
        do {
            a.push_back(x % BASE);
            x /= BASE;
        } while (x);
        trim();
    }
    BigNum(const string &s) : sign(1) {
        a.clear();
        int start = 0;
        if (!s.empty() && (s[0] == '-' || s[0] == '+')) {
            if (s[0] == '-') sign = -1;
            start = 1;
        }
        if (start == (int)s.size())
            throw invalid_argument("Invalid BigNum");
        for (int i = start; i < (int)s.size(); i++) {
            if (!isdigit((unsigned char)s[i]))
                throw invalid_argument("Invalid BigNum");
        }
        for (int i = (int)s.size(); i > start; i -= BASE_DIGITS) {
            int l = max(start, i - BASE_DIGITS);
            a.push_back(stoi(s.substr(l, i - l)));
        }
        if (a.empty()) a.push_back(0);
        trim();
    }
    void trim() {
        while (a.size() > 1 && a.back() == 0)
            a.pop_back();
        if (a.empty()) a.push_back(0);
        if (a.size() == 1 && a[0] == 0)
            sign = 1;
    }
    bool isZero() const {
        return a.size() == 1 && a[0] == 0;
    }
    BigNum abs() const {
        BigNum res = *this;
        res.sign = 1;
        return res;
    }
    BigNum operator-() const {
        BigNum res = *this;
        if (!res.isZero()) res.sign = -res.sign;
        return res;
    }
    // Compare absolute values: -1, 0, +1.
    static int compareAbs(const BigNum &x, const BigNum &y) {
        if (x.a.size() != y.a.size())
            return x.a.size() < y.a.size() ? -1 : 1;
        for (int i = (int)x.a.size() - 1; i >= 0; i--) {
            if (x.a[i] != y.a[i])
                return x.a[i] < y.a[i] ? -1 : 1;
        }
        return 0;
    }
    // |this| += |v|
    void addAbs(const BigNum &v) {
        ll carry = 0;
        size_t n = max(a.size(), v.a.size());
        a.resize(n, 0);
        for (size_t i = 0; i < n || carry; i++) {
            if (i == a.size()) a.push_back(0);
            ll cur = carry + a[i]
                   + (i < v.a.size() ? v.a[i] : 0LL);
            a[i] = cur % BASE;
            carry = cur / BASE;
        }
    }
    // Requires |this| >= |v|.
    void subAbs(const BigNum &v) {
        ll borrow = 0;
        for (size_t i = 0; i < a.size(); i++) {
            ll cur = (ll)a[i] - borrow
                   - (i < v.a.size() ? v.a[i] : 0LL);
            if (cur < 0) {
                cur += BASE;
                borrow = 1;
            } else {
                borrow = 0;
            }
            a[i] = cur;
        }
        trim();
    }
    // Addition with signs.
    BigNum &operator+=(const BigNum &v) {
        if (sign == v.sign) {
            addAbs(v);
        } else {
            int cmp = compareAbs(*this, v);

            if (cmp == 0) {
                a.assign(1, 0);
                sign = 1;
            } else if (cmp > 0) {
                subAbs(v);
            } else {
                BigNum res = v;
                res.subAbs(*this);
                *this = move(res);
            }
        }
        trim();
        return *this;
    }
    BigNum &operator-=(const BigNum &v) {
        return *this += (-v);
    }
    // Multiply by a small nonnegative integer.
    BigNum mulSmall(ll m) const {
        assert(0 <= m && m <= BASE);
        if (m == 0 || isZero()) return BigNum(0);
        BigNum res;
        res.a.clear();
        res.sign = sign;
        i128 carry = 0;
        for (int digit : a) {
            i128 cur = (i128)digit * m + carry;
            res.a.push_back((int)(cur % BASE));
            carry = cur / BASE;
        }
        while (carry > 0) {
            res.a.push_back((int)(carry % BASE));
            carry /= BASE;
        }
        res.trim();
        return res;
    }
    // Multiplication: O(number_of_blocks^2).
    BigNum &operator*=(const BigNum &v) {
        if (isZero() || v.isZero()) {
            a.assign(1, 0);
            sign = 1;
            return *this;
        }
        vector<int> res(a.size() + v.a.size() + 1, 0);
        for (int i = 0; i < (int)a.size(); i++) {
            i128 carry = 0;
            for (int j = 0;
                j < (int)v.a.size() || carry; j++) {
                i128 cur = res[i + j] + carry;
                if (j < (int)v.a.size())
                    cur += (i128)a[i] * v.a[j];
                res[i + j] = (int)(cur % BASE);
                carry = cur / BASE;
            }
        }
        sign *= v.sign;
        a = move(res);
        trim();
        return *this;
    }
    // Divide magnitude by a positive small integer.
    void divSmall(int v) {
        assert(v > 0);
        i128 remainder = 0;
        for (int i = (int)a.size() - 1; i >= 0; i--) {
            i128 cur = remainder * BASE + a[i];
            a[i] = (int)(cur / v);
            remainder = cur % v;
        }
        trim();
    }
    // Replace remainder with remainder * BASE + digit.
    void shiftBaseAdd(int digit) {
        if (isZero()) {
            a[0] = digit;
            sign = 1;
        } else {
            a.insert(a.begin(), digit);
        }

        trim();
    }
    // Returns {quotient, remainder}.
    // Quotient truncates toward zero.
    // Remainder has the dividend's sign.
    static pair<BigNum, BigNum> divmod(
        const BigNum &x, const BigNum &y
    ) {
        if (y.isZero())
            throw domain_error("Division by zero");
        BigNum a = x.abs();
        BigNum b = y.abs();
        if (compareAbs(a, b) < 0)
            return {BigNum(0), x};
        // Normalize the divisor for quotient estimation.
        int norm = BASE / (b.a.back() + 1LL);
        a = a.mulSmall(norm);
        b = b.mulSmall(norm);
        BigNum quotient;
        quotient.a.assign(a.a.size(), 0);
        BigNum remainder(0);
        for (int i = (int)a.a.size() - 1; i >= 0; i--) {
            remainder.shiftBaseAdd(a.a[i]);
            ll s1 = remainder.a.size() > b.a.size()
                  ? remainder.a[b.a.size()] : 0;
            ll s2 = remainder.a.size() >= b.a.size()
                  ? remainder.a[b.a.size() - 1] : 0;
            ll digit = (ll)(
                ((i128)BASE * s1 + s2) / b.a.back()
            );
            // Estimate can temporarily reach BASE.
            if (digit > BASE) digit = BASE;
            remainder -= b.mulSmall(digit);
            while (remainder.sign < 0) {
                remainder += b;
                --digit;
            }
            quotient.a[i] = (int)digit;
        }
        quotient.sign = x.sign * y.sign;
        quotient.trim();
        remainder.divSmall(norm);
        remainder.sign = x.sign;
        remainder.trim();
        return {quotient, remainder};
    }
    BigNum &operator/=(const BigNum &v) {
        *this = divmod(*this, v).first;
        return *this;
    }
    BigNum &operator%=(const BigNum &v) {
        *this = divmod(*this, v).second;
        return *this;
    }
    friend BigNum operator+(BigNum x, const BigNum &y) {
        return x += y;
    }
    friend BigNum operator-(BigNum x, const BigNum &y) {
        return x -= y;
    }
    friend BigNum operator*(BigNum x, const BigNum &y) {
        return x *= y;
    }
    friend BigNum operator/(const BigNum &x, const BigNum &y) {
        return divmod(x, y).first;
    }
    friend BigNum operator%(const BigNum &x, const BigNum &y) {
        return divmod(x, y).second;
    }
    friend bool operator==(const BigNum &x, const BigNum &y) {
        return x.sign == y.sign && x.a == y.a;
    }
    friend bool operator!=(const BigNum &x, const BigNum &y) {
        return !(x == y);
    }
    friend bool operator<(const BigNum &x, const BigNum &y) {
        if (x.sign != y.sign) return x.sign < y.sign;

        int cmp = compareAbs(x, y);
        return x.sign == 1 ? cmp < 0 : cmp > 0;
    }
    friend bool operator>(const BigNum &x, const BigNum &y) {
        return y < x;
    }
    friend bool operator<=(const BigNum &x, const BigNum &y) {
        return !(y < x);
    }
    friend bool operator>=(const BigNum &x, const BigNum &y) {
        return !(x < y);
    }
    friend ostream &operator<<(ostream &out, const BigNum &x) {
        if (x.sign == -1) out << '-';
        out << x.a.back();
        for (int i = (int)x.a.size() - 2; i >= 0; i--) {
            string part = to_string(x.a[i]);
            out << string(BASE_DIGITS - part.size(), '0')
                << part;
        }
        return out;
    }
    friend istream &operator>>(istream &in, BigNum &x) {
        string s;
        in >> s;
        if (in) x = BigNum(s);
        return in;
    }
};

int main(){
    
}
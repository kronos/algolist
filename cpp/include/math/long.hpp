//
// Created by Ivan Samsonov on 2019-06-07.
//

#ifndef LONG_HPP
#define LONG_HPP

#include "common.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>

const ll base = 1000*1000*1000;

class Long {
    std::vector<int> data;
    bool negative;
    size_t len;

    void normalize() {
        while (len > 1 && data[len-1] == 0) {
            len--;
        }
    }

public:
    Long(): Long(0) {
    }

    Long(int value): Long(ll(value)) {
    }

    Long(ll value) {
        negative = value < 0;

        do {
            data.push_back(std::abs(value) % base);
            value /= base;
        } while (value != 0);

        len = data.size();
    }

    explicit Long(const std::string& value) {
        if (value.empty()) {
            data.push_back(0);
            len = 1;
        } else {
            negative = value[0] == '-';
            ll carry = 0;
            ll p = 1;
            int to = value[0] == '-' || value[0] == '+' ? 1 : 0;

            // ignore trailing zeroes
            while (to < value.length() - 1 && value[to] == '0') {
                to++;
            }

            for (int i = value.length()-1; i >= to; i--, p *= 10) {
                assert((value[i] - '0') >= 0 && (value[i] - '0') < 10);
                carry += (value[i] - '0')*p;
                if (p >= base) {
                    data.push_back(carry % base);
                    carry /= base;
                    p = 1;
                }
            }

            if (carry || data.empty()) {
                data.push_back(carry);
            }

            len = data.size();
            negative = value[0] == '-' && !is_zero();
        }
    }

    Long(const Long& value):
        negative(value.negative), len(value.len), data(value.data.begin(), value.data.begin() + value.len) {
    }

    std::string to_string() const {
        std::stringstream ss;
        if (negative) {
            ss << "-";
        }

        ss << data[len-1];

        for (int i = len-2; i >= 0; i--) {
            ss << std::setw(9) << std::setfill('0') << data[i];
        }

        return ss.str();
    }

    bool is_zero() const {
        return data[len-1] == 0;
    }

    Long operator - () const {
        Long result(*this);
        result.negative = !is_zero() && !result.negative;
        return result;
    }

    Long operator - (const Long& other) const {
        if (negative != other.negative) {
            Long result = len < other.len ?  add(other, *this) :  add(*this, other);
            result.negative = negative && !result.is_zero();
            return result;
        }

        int cmp = compare(*this, other, true);
        Long result;

        if (cmp == -1) {
            result = sub(other, *this);
            result.negative = !other.negative;
        } else if (cmp == 1) {
            result = sub(*this, other);
            result.negative = negative;
        }

        return result;
    }

    Long operator + (const Long& other) const {
        Long result;

        if (negative != other.negative) {
            int cmp = compare(*this, other, true);
            if (cmp == -1) {
                result = sub(other, *this);
            } else if (cmp == 1) {
                result = sub(*this, other);
            }
        } else {
            result = len < other.len ?  add(other, *this) :  add(*this, other);
            result.negative = negative;
        }

        return result;
    }

    Long operator * (const Long& other) const {
        Long result;
        if (!(is_zero() || other.is_zero())) {
            result = mul(*this, other);
            result.negative = negative ^ other.negative;
        }

        return result;
    }

//    Long operator % (const Long& other) const {
//        Long q = this/other;
//        return q - other;
//    }

    bool operator < (const Long& other) const {
        return compare(*this, other, false) == -1;
    }

    bool operator > (const Long& other) const {
        return compare(*this, other, false) == 1;
    }

    bool operator <= (const Long& other) const {
        return compare(*this, other, false) < 1;
    }

    bool operator >= (const Long& other) const {
        return compare(*this, other, false) > -1;
    }

    bool operator == (const Long& other) const {
        return compare(*this, other, false) == 0;
    }

    bool operator != (const Long& other) const {
        return compare(*this, other, false) != 0;
    }

    Long& operator += (const Long& other) {
        return *this = *this + other;
    }

    Long& operator -= (const Long& other) {
        if (this == &other) {
            return *this = Long();
        }

        return *this = Long(*this) - other;
    }

    Long& operator *= (const Long& other) {
        return *this = *this * other;
    }

    Long& operator++() {
        return *this += 1;
    }

    Long operator++(int) {
        Long result(*this);
        *this += 1;
        return result;
    }

    Long& operator--() {
        return *this -= 1;
    }

    Long operator--(int) {
        Long result(*this);
        *this -= 1;
        return result;
    }

    friend std::ostream& operator << (std::ostream& os, const Long &value);
    friend int compare(const Long &left, const Long &right, bool modulo);
    friend Long add(const Long &left, const Long &right);
    friend Long sub(const Long &left, const Long &right);
    friend Long mul(const Long &left, const Long &right);
};

std::ostream& operator << (std::ostream& os, const Long &value) {
    if (value.negative) {
        os << "-";
    }

    os << value.data[value.len-1];

    for (int i = value.len-2; i >= 0; i--) {
        os << std::setw(9) << std::setfill('0') << value.data[i];
    }
    return os;
}

std::istream& operator >> (std::istream& is, Long &value) {
    std::string s;
    is >> s;
    value = Long(s);
    return is;
}

// -1 less, 0 equal, 1 more
int compare(const Long &left, const Long &right, bool modulo) {
    int result = modulo ? 1 : (left.negative ? -1 : 1);

    if (!modulo && left.negative != right.negative) {
        return result;
    }

    if (left.len != right.len) {
        return left.len < right.len ? -result : result;
    }

    for (int idx = left.len - 1; idx >= 0; idx--) {
        if (left.data[idx] != right.data[idx]) {
            return left.data[idx] < right.data[idx] ? -result : result;
        }
    }

    return 0;
}

// left.len >= right.len
Long add(const Long &left, const Long &right) {
    Long result(left);

    ll carry = 0;
    for (size_t idx = 0; idx < right.len; idx++) {
        result.data[idx] += right.data[idx] + carry;
        carry = result.data[idx] >= base;
        if (carry) {
            result.data[idx] %= base;
        }
    }

    if (carry) {
        if (right.len == result.data.size()) {
            result.data.push_back(carry);
            result.len++;
        } else {
            result.data[right.len] += carry;
        }
    }

    return result;
}

// left >= right
Long sub(const Long &left, const Long &right) {
    Long result(left);

    ll carry = 0;
    int idx = 0;

    for (; idx < right.len; idx++) {
        result.data[idx] = result.data[idx] - right.data[idx] + carry;
        if (result.data[idx] < 0) {
            result.data[idx] += base;
            carry = -1;
        } else {
            carry = 0;
        }
    }

    for (; (idx < result.len) && carry; idx++) {
        result.data[idx] += carry;
        if (result.data[idx] < 0) {
            result.data[idx] += base;
            carry = -1;
        } else {
            carry = 0;
        }
    }

    if (carry) {
        if (result.data.size() > result.len) {
            result.data[result.len] = std::abs(carry);
        } else {
            result.data.push_back(std::abs(carry));
        }

        result.len++;
    }

    result.normalize();

    return result;
}

Long mul(const Long &left, const Long &right) {
    Long result;

    result.len = left.len + right.len;
    result.data.resize(result.len, 0);

    ll carry;
    for (size_t i = 0; i < left.len; i++) {
        carry = 0;
        for (size_t j = 0; j < right.len; j++) {
            carry = (ll)left.data[i] * right.data[j] + carry + result.data[i+j];
            result.data[i+j] = carry % base;
            carry = carry / base;
        }
        result.data[i+right.len] = carry;
    }

    result.normalize();

    return result;
}
#endif // LONG_HPP

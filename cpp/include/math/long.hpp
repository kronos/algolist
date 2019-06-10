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

const ll base = 1000'000'000;

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
        if (negative != other.negative) {
            sub(*this, other, other.negative);
        } else {
            add(*this, other);
        }
        return *this;
    }

    Long& operator -= (const Long& other) {
        if (negative == other.negative) {
            sub(*this, other, !other.negative);
        } else {
            add(*this, other);
        }

        return *this;
    }

    Long& operator *= (const Long& other) {
        if (other.is_zero()) {
            *this = Long();
        } else if (!is_zero()) {
            if (this == &other) {
                mul(*this, Long(other));
            } else {
                mul(*this, other);
            }
        }

        return *this;
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
    friend void mul(Long &left, const Long &right);
    friend void add(Long &result, const Long &right);
    friend void sub(Long &result, const Long &right, bool right_negative);
    friend Long operator+(Long left, const Long& right);
    friend Long operator-(Long left, const Long& right);
    friend Long operator*(Long left, const Long& right);
};

Long operator+(Long left, const Long& right) {
    return left += right;
}

Long operator-(Long left, const Long& right) {
    return left -= right;
}

Long operator*(Long left, const Long& right) {
    return left *= right;
}

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

void mul(Long &left, const Long &other) {
    std::vector<int> original(left.data.begin(), left.data.begin() + left.len);

    left.len += other.len;
    left.data = std::vector<int>(left.len, 0);
    left.negative = left.negative ^ other.negative;

    ll carry = 0;
    for (size_t i = 0; i < original.size(); i++) {
        carry = 0;
        for (size_t j = 0; j < other.len; j++) {
            carry = (ll)original[i] * other.data[j] + carry + left.data[i+j];
            left.data[i+j] = carry % base;
            carry = carry / base;
        }
        left.data[i+other.len] = carry;
    }

    left.normalize();
}

void add(Long &result, const Long &right) {
    ll carry = 0;
    result.len = std::max(result.len, right.len);
    if (result.data.size() < result.len){
        result.data.resize(result.len, 0);
    }

    for (size_t idx = 0; idx < right.len; idx++) {
        result.data[idx] += right.data[idx] + carry;
        carry = result.data[idx] >= base;
        if (carry) {
            result.data[idx] -= base;
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
}

void sub(Long &result, const Long &right, bool right_negative) {
    ll carry = 0;
    ll sign = 1;
    if (compare(result, right, true) < 1) {
        sign = result.negative && right_negative ? 1 : -1;
        result.negative = right_negative;
    }

    result.len = std::max(result.len, right.len);
    if (result.data.size() < result.len){
        result.data.resize(result.len, 0);
    }

    int idx = 0;
    for (; idx < right.len; idx++) {
        result.data[idx] = (result.data[idx] - right.data[idx])*sign + carry;
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
    result.negative = result.negative && !result.is_zero();
}

#endif // LONG_HPP

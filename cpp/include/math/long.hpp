//
// Created by Ivan Samsonov on 2019-06-07.
//

#ifndef LONG_HPP
#define LONG_HPP

#include "common.hpp"
#include <iostream>
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

    inline int handle_carry(size_t idx) {
        int carry;
        if (data[idx] < 0) {
            data[idx] += base;
            carry = -1;
        } else {
            carry = data[idx] >= base;
            if (carry) {
                data[idx] %= base;
            }
        }

        return carry;
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
        Long result(*this);
        result -= other;
        return result;
    }

    Long operator + (const Long& other) const {
        Long result(*this);
        result += other;
        return result;
    }

    Long operator * (const Long& other) const {
        Long result(*this);
        result *= other;
        return result;
    }

//    Long operator % (const Long& other) const {
//        Long q = this/other;
//        return q - other;
//    }

    bool operator < (const Long& other) const {
        if (negative != other.negative) {
            return negative;
        }

        if (len != other.len) {
            return negative ? len > other.len : len < other.len;
        }

        for (int i = len-1; i >= 0; i--) {
            if (data[i] != other.data[i]) {
                return negative ? data[i] > other.data[i] : data[i] < other.data[i];
            }
        }

        return false; // equal
    }

    bool operator > (const Long& other) const {
        if (negative != other.negative) {
            return !negative;
        }

        if (len != other.len) {
            return negative ? len < other.len : len > other.len;
        }

        for (int i = len-1; i >= 0; i--) {
            if (data[i] != other.data[i]) {
                return negative ? data[i] < other.data[i] : data[i] > other.data[i];
            }
        }

        return false; // equal
    }

    bool operator <= (const Long& other) const {
        return !(*this > other);
    }

    bool operator >= (const Long& other) const {
        return !(*this < other);
    }

    bool operator == (const Long& other) const {
        bool is_equal = negative == other.negative && len == other.len;

        for (int i = 0; (i < len) && is_equal; i++) {
            is_equal = data[i] == other.data[i];
        }

        return is_equal;
    }

    bool operator != (const Long& other) const {
        return !(*this == other);
    }

    Long& operator += (const Long& other) {
        ll this_sign = 1;
        ll other_sign = 1;
        ll carry = 0;

        if (negative != other.negative) {
            this_sign = negative ? -1 : 1;
            other_sign = -this_sign;

            negative = !negative;
            negative = *this > other;

            if (negative) {
                this_sign = -this_sign;
                other_sign = -this_sign;
            }
        }

        for (size_t i = len; i < other.len; i++) {
            data.push_back(0);
        }

        len = std::max(len, other.len);

        int idx = 0;
        for (; idx < other.len; idx++) {
            data[idx] = this_sign*data[idx] + other_sign*other.data[idx] + carry;
            carry = handle_carry(idx);
        }

        for (; (idx < len) && carry; idx++) {
            data[idx] += carry;
            carry = handle_carry(idx);
        }

        if (carry) {
            if (data.size() > len) {
                data[len] = std::abs(carry);
            } else {
                data.push_back(std::abs(carry));
            }

            len++;
        }

        normalize();

        return *this;
    }

    Long& operator -= (const Long& other) {
        return *this += -other;
    }

    Long& operator *= (const Long& other) {
        std::vector<int> original(data.begin(), data.begin()+len);
        std::fill(data.begin(), data.end(), 0);
        negative = negative ^ other.negative;

        size_t total_len = len + other.len;
        if (data.size() < total_len) {
            data.resize(total_len, 0);
        }

        ll carry;
        for (size_t i = 0; i < len; i++) {
            carry = 0;
            for (size_t j = 0; j < other.len; j++) {
                carry = (ll)original[i] * other.data[j] + carry + data[i+j];
                data[i+j] = carry % base;
                carry = carry / base;
            }
            data[i+other.len] = carry;
        }

        len = total_len;

        normalize();

        negative = negative && !is_zero();

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

#endif // LONG_HPP

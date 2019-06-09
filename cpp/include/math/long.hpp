//
// Created by Ivan Samsonov on 2019-06-07.
//

#ifndef LONG_HPP
#define LONG_HPP

#include "common.hpp"
#include <sstream>
#include <iomanip>

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

    explicit Long(int value): Long(ll(value)) {
    }

    explicit Long(ll value) {
        negative = value < 0;

        do {
            data.push_back(abs(value) % base);
            value /= base;
        } while (value != 0);

        len = data.size();
    }

    explicit Long(const std::string& value) {
        if (value.empty()) {
            data.push_back(0);
        } else {
            negative = value[0] == '-';
            ll carry = 0;
            ll p = 1;
            for (int i = value.length()-1; i >= negative; i--, p *= 10) {
                carry += (value[i] - '0')*p;
                if (p >= base) {
                    data.push_back(carry % base);
                    carry /= base;
                    p /= base;
                }
            }

            if (carry) {
                data.push_back(carry);
            }
        }
        len = data.size();
    }

    Long(const Long& value) {
        data = value.data;
        len = value.len;
        negative = value.negative;
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

//    Long operator * (const Long& other) const {
//        Long result(this);
//        result *= other;
//        return result;
//    }
//
//    Long operator % (const Long& other) const {
//        Long q = this/other;
//        return q - other;
//    }

    bool operator == (const Long& other) const {
        bool is_equal = len == other.len && negative == other.negative;

        for (size_t i = 0; (i < len) && is_equal; i++) {
            is_equal = data[i] == other.data[i];
        }

        return is_equal;
    }

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

    Long& operator += (const Long& other) {
        ll this_sign = 1;
        ll other_sign = 1;
        ll carry = 0;

        if (negative != other.negative) {
            this_sign = negative ? -1 : 1;
            other_sign = other.negative ? -1 : 1;

            negative = !negative;

            negative = *this > other;

            if (negative) {
                this_sign = -this_sign;
                other_sign = -other_sign;
            }
        }

        for (size_t i = len; i < other.len; i++) {
            data.push_back(0);
        }

        len = std::max(len, other.len);

        int idx = 0;
        for (; idx < other.len; idx++) {
            carry += this_sign*data[idx] + other_sign*other.data[idx];
            if (carry < 0) {
                data[idx] = (carry + base) % base;
                carry = -1;
            } else {
                data[idx] = carry % base;
                carry = carry >= base;
            }
        }

        for (; (idx < len) && carry; idx++) {
            carry += data[idx];
            if (carry < 0) {
                data[idx] = (carry + base) % base;
                carry = -1;
            } else {
                data[idx] = carry % base;
                carry = carry >= base;
            }
        }

        if (carry) {
            if (data.size() > len) {
                data[len] = abs(carry);
            } else {
                data.push_back(abs(carry));
            }

            len++;
        }

        normalize();

        return *this;
    }

    Long& operator -= (const Long& other) {
        return *this += -other;
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

    ll to_long() const {
        ll result = data[0];

        if (len > 1) {
            result += data[1]*base;

            if (len > 2) {
                result += data[2]*base*base;
            }
        }

        return negative ? -result : result;
    }

    int to_int() const {
        return (int)long();
    }

    bool is_zero() const {
        return data[0] == 0 && len == 1;
    }
};
#endif //LONG_HPP

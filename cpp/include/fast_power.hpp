//
// Created by Ivan Samsonov on 2019-05-26.
//

#ifndef FAST_POWER_HPP
#define FAST_POWER_HPP

#include "common.hpp"

// Fast exponentiation
// Original implementation was taken from https://cp-algorithms.com/algebra/binary-exp.html
template <typename T>
T fast_power(T number, size_t power) {
    assert(power); // use external check for zero
    T result = number;

    for (--power; power > 0; power >>= 1U) {
        if (power & 1U) {
            result = result * number;
        }
        number = number * number;
    }

    return result;
}

#endif // FAST_POWER_HPP

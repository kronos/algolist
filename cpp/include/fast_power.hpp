//
// Created by Ivan Samsonov on 2019-05-26.
//

#ifndef FAST_POWER_HPP
#define FAST_POWER_HPP

// Fast exponentiation
// implementation was taken from https://cp-algorithms.com/algebra/binary-exp.html
template <typename T>
T fast_power(T number, size_t power) {
    assert(power); // use external check for zero
    T res = number;
    while (power) {
        if (power & 1) {
            res = res * number;
        }
        number = number * number;
        power >>= 1;
    }
    return res;
}

// Fast exponentiation by modulo
template <typename T,typename M>
T fast_power_mod(T number, size_t power, M mod) {
    assert(power); // use external check for zero
    T res = number;
    while (power) {
        if (power & 1) {
            res = (res * number) % mod;
        }
        number = (number * number) % mod;
        power >>= 1;
    }
    return res;
}

#endif // FAST_POWER_HPP

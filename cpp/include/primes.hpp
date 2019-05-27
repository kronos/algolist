//
// Created by Ivan Samsonov on 2019-05-26.
//

#ifndef PRIMES_HPP
#define PRIMES_HPP

#include <bitset>
#include "euclid.hpp"

// check if number is prime
template<typename T>
bool is_prime(T number) {
    assert(number >= 0);
    bool prime = number == 2 || (number > 2 && number%2 != 0);

    if (prime) {
        for (T counter = 3; (counter*counter <= number) && prime; counter += 2) {
            prime = number % counter > 0;
        }
    }

    return prime;
}

// check first N numbers for simplicity in O(N)
template<size_t N>
std::bitset<N> mark_primes() {
    assert(N);
    std::bitset<N> is_primes;
    is_primes.set();
    is_primes.flip(0);

    if (is_primes.size() > 1) {
        is_primes.flip(1);
    }

    for (size_t number = 2; number < is_primes.size(); number++) {
        if (is_primes.test(number)) {
            for (int idx = number*number; idx < is_primes.size(); idx += number) {
                is_primes.flip(idx);
            }
        }
    }

    return is_primes;
}

// check if numbers are coprime
template<typename T>
bool is_coprime(T a, T b) {
    return gcd(a, b) == 1;
}

#endif // PRIMES_HPP

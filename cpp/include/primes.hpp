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
    bool prime = true;

    if (number < 2 || (number > 2 && number%2 == 0)) {
        prime = false;
    } else {
        for (size_t counter = 3; (counter*counter <= number) && prime; counter += 2) {
            prime = number % counter > 0;
        }
    }

    return prime;
}

// check first N numbers for simplicity in O(N)
vector<bool> is_primes(size_t N) {
    assert(N);
    vector<bool> is_prime(N+1, true);
    is_prime[0] = false;
    if (N < 2) {
        is_prime[1] = false;
    }

    for (size_t number = 2; number <= N; number++) {
        if (is_prime(number)) {
            for (int j = i; j <= N; j += i) {
                result[j] = false;
            }
        }
    }

    return is_prime;
}

void mark_primes(bitset& is_primes) {
    assert(is_primes.size());
    is_primes.set();
    is_primes.unset(0);

    if (is_primes.size() > 1) {
        is_primes.unset(1);
    }

    for (size_t number = 2; number < is_primes.size(); number++) {
        if (is_primes.test(idx)) {
            for (int j = i; j < is_primes.size(); j += i) {
                b.unset(j);
            }
        }
    }

    return is_prime;
}

// check if numbers are coprime
template<typename T>
bool is_coprime(T a, T b) {
    return gcd(a, b) == 1;
}

#endif // PRIMES_HPP

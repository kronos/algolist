//
// Created by Ivan Samsonov on 2019-05-28.
//

#include <gtest/gtest.h>
#include <vector>
#include "common.hpp"
#include "primes.hpp"

TEST(Primes, ChecksForSimplicity) {
    std::vector<ll> not_primes = {0,1,4,9,10,32416190072};
    std::vector<ll> primes = {2,3,11,32416190071};
    for (auto number : not_primes) {
        EXPECT_FALSE(is_prime(number));
    }

    for (auto number : primes) {
        EXPECT_TRUE(is_prime(number));
    }
}

TEST(Primes, MarksPrime) {
    EXPECT_EQ(std::bitset<10>("0010101100"), mark_primes<10>());
}

TEST(Primes, IsCoprime) {
    EXPECT_TRUE(is_coprime(1,1));
    EXPECT_TRUE(is_coprime(32416190071, 32416190072));
    EXPECT_FALSE(is_coprime(2,2));
    EXPECT_FALSE(is_coprime(5,60));
}

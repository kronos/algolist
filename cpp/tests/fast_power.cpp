//
// Created by Ivan Samsonov on 2019-06-02.
//


#include <gtest/gtest.h>
#include "fast_power.hpp"

TEST(FastPower, FastPower) {
    EXPECT_EQ(fast_power(1000000, 1), 1000000);
    EXPECT_EQ(fast_power(1, 1000000), 1);
    EXPECT_EQ(fast_power(2LL, 62), 4611686018427387904LL);
    EXPECT_EQ(fast_power(5LL, 20), 95367431640625LL);
}

//
// Created by Ivan Samsonov on 2019-06-05.
//

#include <gtest/gtest.h>
#include "fibonacci.hpp"

TEST(Fibonacci, FastFibonacci) {
    std::vector<size_t> numbers = {0, 1, 2, 10, 20, 93};
    std::vector<ull> answers = {0ULL, 1ULL, 1ULL, 55ULL, 6765ULL, 12200160415121876738ULL};
    for (size_t idx = 0; idx < numbers.size(); idx++) {
        EXPECT_EQ(answers[idx], fast_fibonacci<ull>(numbers[idx]));
    }
}

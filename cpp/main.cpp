//
// Created by Ivan Samsonov on 2019-05-26.
//

#include <iostream>

#include "common.hpp"
#include "disjoint_set.hpp"
#include "matrix.hpp"
#include "fast_power.hpp"
#include "fibonacci.hpp"

int main() {
    for (int i = 1; i <= 20; i++) {
        std::cout << fast_fibonacci<ll>(i) << ", ";
    }
    return 0;
}
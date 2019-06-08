//
// Created by Ivan Samsonov on 2019-05-26.
//

#ifndef FIBONACCI_HPP
#define FIBONACCI_HPP

#include "common.hpp"
#include "matrix.hpp"

template <typename T>
T fast_fibonacci(size_t N) {
    if (!N) {
        return zero<T>();
    } else if (N <= 2) {
        return one<T>();
    }

    Matrix<T> m({{one<T>(), one<T>()}, {one<T>(), zero<T>()}});

    return m.power(N)[0][1];
}

#endif // FIBONACCI_HPP

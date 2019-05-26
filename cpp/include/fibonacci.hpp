//
// Created by Ivan Samsonov on 2019-05-26.
//

#ifndef FIBONACCI_HPP
#define FIBONACCI_HPP

template <typename T>
T fast_fibonacci(size_t N) {
    T zero = T();
    T one = zero + 1;

    if (!N) {
        return zero;
    } else if (N < 2) {
        return one;
    }

    Matrix<T> m({{one, one}, {one, zero}});

    return m.power(N - 1)[0][1];
}

#endif // FIBONACCI_HPP

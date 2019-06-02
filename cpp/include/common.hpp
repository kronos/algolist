//
// Created by Ivan Samsonov on 2019-05-26.
//

#ifndef COMMON_HPP
#define COMMON_HPP

#include <cstddef>
#include <cassert>

typedef long long ll;

template<typename T>
T zero() {
    return T();
}

template<typename T>
T one() {
    return zero<T>() + 1;
}

#endif // COMMON_HPP

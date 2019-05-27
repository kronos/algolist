//
// Created by Ivan Samsonov on 2019-05-26.
//

#ifndef EUCLID_HPP
#define EUCLID_HPP

// compute gcd
template<typename T>
T gcd(T a, T b) {
    T t;
    while (b) {
        t = a % b;
        a = b;
        b = t;
    }

    return a;
}

// compute lcm
template<typename T>
T lcm(T a, T b) {
    assert(a != 0 || b != 0);
    return (a/gcd(a, b)) * b;
}

#endif // EUCLID_HPP

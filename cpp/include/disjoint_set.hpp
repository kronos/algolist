//
// Created by Ivan Samsonov on 2019-05-26.
//

#ifndef DISJOINT_SET_HPP
#define DISJOINT_SET_HPP

#include <vector>

// Disjoint sets (https://en.wikipedia.org/wiki/Disjoint_sets) implementation
template <typename T>
class DisjointSets {
    std::vector<T> P;
    std::vector<T> R;

public:
    explicit DisjointSets(size_t size) {
        P.resize(size);
        R.resize(size, 0);
    }

    void init(T idx) {
        P[idx] = idx;
        R[idx] = 0;
    }

    void init_with_value(T idx, T value) {
        P[idx] = value;
        R[idx] = 0;
    }

    T parent(T idx) {
        if (idx != P[idx]) {
            P[idx] = parent(P[idx]);
        }

        return P[idx];
    }

    T get_parent(T idx) {
        return P[idx];
    }

    void unite(T i, T j) {
        i = parent(i);
        j = parent(j);

        if (i != j) {
            if (R[i] > R[j]) {
                P[j] = i;
            } else {
                P[i] = j;
                if (R[i] == R[j]) {
                    R[j]++;
                }
            }
        }
    }
};

#endif // DISJOINT_SET_HPP

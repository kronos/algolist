//
// Created by Ivan Samsonov on 2019-05-26.
//

#ifndef CPP_MATRIX_HPP
#define CPP_MATRIX_HPP

#include <vector>
#include "fast_power.hpp"

template <typename T>
class Matrix {
    std::vector<std::vector<T>> data;
    std::pair<size_t, size_t> dim;

public:
    Matrix(size_t n, size_t m): dim({n,m}) {
        assert(n && m);
        data.resize(n, std::vector<T>(m, T()));
    }

    explicit Matrix(std::pair<size_t, size_t> p): Matrix(p.first, p.second) {}
    explicit Matrix(const std::vector<std::vector<T>>& new_data) {
        assert(!(new_data.empty() && new_data[0].empty()));
        data = new_data;
        dim = {data.size(), data[0].size()};
    }

    Matrix(const Matrix& other): dim(other.dim), data(other.data) {}

    std::vector<T>& operator[] (size_t idx) {
        assert(idx < data.size());
        return data[idx];
    }

    std::vector<T> operator[] (size_t idx) const {
        assert(idx < data.size());
        return data[idx];
    }

    Matrix operator* (const Matrix& other) const {
        assert(dim.first == other.dim.second && dim.second == other.dim.first);
        Matrix result(dim.first, other.dim.second);
        for (int i = 0; i < dim.first; ++i) {
            for (int j = 0; j < other.dim.second; ++j) {
                result[i][j] = data[i][0] * other.data[0][j];
                for (int k = 1; k < dim.second; ++k) {
                    result[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }

        return result;
    }

    Matrix& operator *=(const Matrix& other) {
        assert(dim.first == other.dim.second && dim.second == other.dim.first);
        return *this = *this * other;
    }
};

#endif //CPP_MATRIX_HPP

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
        data.resize(n, std::vector<T>(m, T()));
    }

    explicit Matrix(std::pair<size_t, size_t> p): Matrix(p.first, p.second) {}
    explicit Matrix(const std::vector<std::vector<T>>& new_data) {
        data = new_data;
        dim = {data.size(), 0};
        if (data.size()) {
            dim.second = data[0].size();
        }
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
                result[i][j] = T();
                for (int k = 0; k < dim.second; ++k) {
                    result[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }

        return result;
    }

    Matrix& operator *=(const Matrix& other) const {
        assert(dim.first == other.dim.second && dim.second == other.dim.first);
        Matrix result(*this);

        for (int i = 0; i < dim.first; ++i) {
            for (int j = 0; j < other.dim.second; ++j) {
                data[i][j] = T();
                for (int k = 0; k < dim.second; ++k) {
                    data[i][j] += result.data[i][k] * other.data[k][j];
                }
            }
        }

        return this;
    }

    Matrix power(size_t power) const {
        assert(power);
        Matrix result(*this);

        if (power < 2) {
            return result;
        }

        return fast_power(result, power);
    }
};

#endif //CPP_MATRIX_HPP

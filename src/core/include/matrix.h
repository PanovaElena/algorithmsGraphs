#pragma once
#include <vector>
#include <algorithm>

template <class T>
class Matrix {

    T defaultValue;
    std::vector<T> data;
    size_t n = 0;

public:

    Matrix(T defaultValue = T()) : defaultValue(defaultValue) {}

    Matrix(size_t n, T defaultValue = T()) : defaultValue(defaultValue),
        data(n, defaultValue) {}

    friend bool operator==(const Matrix& m1, const Matrix& m2) {
        return m1.data == m2.data;
    }

    friend bool operator!=(const Matrix& m1, const Matrix& m2) {
        return !(m1 == m2);
    }

    size_t size() const {
        return n;
    }

    void resize(size_t n) {
        std::vector<T> newData(n * n, defaultValue);
        size_t minSize = std::min(this->n, n);

        for (size_t i = 0; i < minSize; ++i)
            for (size_t j = 0; j < minSize; ++j) {
                newData[getIndex(i, j)] = data[getIndex(i, j)];
        }

        std::swap(data, newData);
        this->n = n;
    }

    T& operator() (size_t i, size_t j) {
        return data[getIndex(i, j)];
    }

    T operator() (size_t i, size_t j) const {
        return data[getIndex(i, j)];
    }

    T& operator() (size_t index) {
        return data[index];
    }

    T operator() (size_t index) const {
        return data[index];
    }

    size_t getIndex(size_t i, size_t j) const {
        return i * n + j;
    }

    T getDefaultValue() const {
        return defaultValue;
    }

};

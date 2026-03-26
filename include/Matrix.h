#ifndef HPC_LINALG_MATRIX_H
#define HPC_LINALG_MATRIX_H

#include <vector>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include "Vector.h"

namespace hpc_linalg {

template <typename T>
class Matrix {
public:
    // Constructors
    Matrix() = default;
    Matrix(size_t rows, size_t cols, T initial_value = T{});
    Matrix(const std::vector<std::vector<T>>& data);
    Matrix(std::initializer_list<std::initializer_list<T>> list);

    // Accessors
    size_t rows() const { return rows_; }
    size_t cols() const { return cols_; }
    T& operator()(size_t row, size_t col);
    const T& operator()(size_t row, size_t col) const;

    // Matrix operations
    Matrix<T> transpose() const;
    Matrix<T> operator*(const Matrix<T>& other) const; // Matrix multiplication
    Vector<T> operator*(const Vector<T>& other) const; // Matrix-vector multiplication

    // Element-wise operations
    Matrix<T> operator+(const Matrix<T>& other) const;
    Matrix<T> operator-(const Matrix<T>& other) const;
    Matrix<T> operator*(T scalar) const;
    Matrix<T> operator/(T scalar) const;

    // Compound assignment operators
    Matrix<T>& operator+=(const Matrix<T>& other);
    Matrix<T>& operator-=(const Matrix<T>& other);
    Matrix<T>& operator*=(T scalar);
    Matrix<T>& operator/=(T scalar);

    // Comparison
    bool operator==(const Matrix<T>& other) const;
    bool operator!=(const Matrix<T>& other) const;

    // Stream output
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& mat);

private:
    size_t rows_;
    size_t cols_;
    std::vector<T> data_;

    size_t get_index(size_t row, size_t col) const {
        if (row >= rows_ || col >= cols_) {
            throw std::out_of_range("Matrix index out of range");
        }
        return row * cols_ + col;
    }
};

// Implementations

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols, T initial_value)
    : rows_(rows), cols_(cols), data_(rows * cols, initial_value) {}

template <typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& data) {
    if (data.empty()) {
        rows_ = 0;
        cols_ = 0;
        return;
    }
    rows_ = data.size();
    cols_ = data[0].size();
    for (const auto& row_vec : data) {
        if (row_vec.size() != cols_) {
            throw std::invalid_argument("All rows in matrix must have the same number of columns");
        }
        data_.insert(data_.end(), row_vec.begin(), row_vec.end());
    }
}

template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> list) {
    if (list.size() == 0) {
        rows_ = 0;
        cols_ = 0;
        return;
    }
    rows_ = list.size();
    cols_ = list.begin()->size();
    for (const auto& row_list : list) {
        if (row_list.size() != cols_) {
            throw std::invalid_argument("All rows in matrix must have the same number of columns");
        }
        data_.insert(data_.end(), row_list.begin(), row_list.end());
    }
}

template <typename T>
T& Matrix<T>::operator()(size_t row, size_t col) {
    return data_[get_index(row, col)];
}

template <typename T>
const T& Matrix<T>::operator()(size_t row, size_t col) const {
    return data_[get_index(row, col)];
}

template <typename T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix<T> result(cols_, rows_);
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            result(j, i) = (*this)(i, j);
        }
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {
    if (cols_ != other.rows_) {
        throw std::invalid_argument("Matrix dimensions mismatch for multiplication");
    }
    Matrix<T> result(rows_, other.cols_);
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < other.cols_; ++j) {
            for (size_t k = 0; k < cols_; ++k) {
                result(i, j) += (*this)(i, k) * other(k, j);
            }
        }
    }
    return result;
}

template <typename T>
Vector<T> Matrix<T>::operator*(const Vector<T>& other) const {
    if (cols_ != other.size()) {
        throw std::invalid_argument("Matrix columns must match vector size for multiplication");
    }
    Vector<T> result(rows_);
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            result[i] += (*this)(i, j) * other[j];
        }
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }
    Matrix<T> result(rows_, cols_);
    for (size_t i = 0; i < data_.size(); ++i) {
        result.data_[i] = data_[i] + other.data_[i];
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Matrix dimensions must match for subtraction");
    }
    Matrix<T> result(rows_, cols_);
    for (size_t i = 0; i < data_.size(); ++i) {
        result.data_[i] = data_[i] - other.data_[i];
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(T scalar) const {
    Matrix<T> result(rows_, cols_);
    for (size_t i = 0; i < data_.size(); ++i) {
        result.data_[i] = data_[i] * scalar;
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(T scalar) const {
    if (scalar == T{}) {
        throw std::invalid_argument("Division by zero scalar");
    }
    Matrix<T> result(rows_, cols_);
    for (size_t i = 0; i < data_.size(); ++i) {
        result.data_[i] = data_[i] / scalar;
    }
    return result;
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }
    for (size_t i = 0; i < data_.size(); ++i) {
        data_[i] += other.data_[i];
    }
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Matrix dimensions must match for subtraction");
    }
    for (size_t i = 0; i < data_.size(); ++i) {
        data_[i] -= other.data_[i];
    }
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(T scalar) {
    for (size_t i = 0; i < data_.size(); ++i) {
        data_[i] *= scalar;
    }
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator/=(T scalar) {
    if (scalar == T{}) {
        throw std::invalid_argument("Division by zero scalar");
    }
    for (size_t i = 0; i < data_.size(); ++i) {
        data_[i] /= scalar;
    }
    return *this;
}

template <typename T>
bool Matrix<T>::operator==(const Matrix<T>& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        return false;
    }
    for (size_t i = 0; i < data_.size(); ++i) {
        if (data_[i] != other.data_[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool Matrix<T>::operator!=(const Matrix<T>& other) const {
    return !(*this == other);
}

template <typename U>
std::ostream& operator<<(std::ostream& os, const Matrix<U>& mat) {
    for (size_t i = 0; i < mat.rows(); ++i) {
        os << "[";
        for (size_t j = 0; j < mat.cols(); ++j) {
            os << mat(i, j);
            if (j < mat.cols() - 1) {
                os << ", ";
            }
        }
        os << "]\n";
    }
    return os;
}

} // namespace hpc_linalg

#endif // HPC_LINALG_MATRIX_H

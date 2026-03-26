#ifndef HPC_LINALG_MATRIX_H
#define HPC_LINALG_MATRIX_H

#include <vector>
#include <ostream>
#include <stdexcept>
#include "Vector.h"

class Matrix {
public:
    std::vector<std::vector<double>> data;
    size_t rows_;
    size_t cols_;

    Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
        data.resize(rows, std::vector<double>(cols));
    }

    Matrix(size_t rows, size_t cols, const std::vector<double>& flat_data) : rows_(rows), cols_(cols) {
        if (flat_data.size() != rows * cols) {
            throw std::invalid_argument("Flat data size does not match matrix dimensions");
        }
        data.resize(rows, std::vector<double>(cols));
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                data[i][j] = flat_data[i * cols + j];
            }
        }
    }

    size_t rows() const { return rows_; }
    size_t cols() const { return cols_; }

    double& operator()(size_t r, size_t c) {
        if (r >= rows_ || c >= cols_) {
            throw std::out_of_range("Matrix index out of bounds");
        }
        return data[r][c];
    }

    const double& operator()(size_t r, size_t c) const {
        if (r >= rows_ || c >= cols_) {
            throw std::out_of_range("Matrix index out of bounds");
        }
        return data[r][c];
    }

    Matrix operator*(const Matrix& other) const {
        if (cols_ != other.rows()) {
            throw std::invalid_argument("Matrix dimensions incompatible for multiplication");
        }
        Matrix result(rows_, other.cols());
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < other.cols(); ++j) {
                for (size_t k = 0; k < cols_; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m) {
        for (size_t i = 0; i < m.rows(); ++i) {
            for (size_t j = 0; j < m.cols(); ++j) {
                os << m.data[i][j] << " ";
            }
            os << std::endl;
        }
        return os;
    }
};

#endif // HPC_LINALG_MATRIX_H

#ifndef HPC_LINALG_VECTOR_H
#define HPC_LINALG_VECTOR_H

#include <vector>
#include <ostream>
#include <stdexcept>

class Vector {
public:
    std::vector<double> data;
    size_t size_;

    Vector(size_t size) : size_(size) {
        data.resize(size);
    }

    Vector(const std::vector<double>& vec) : data(vec), size_(vec.size()) {}

    size_t size() const { return size_; }

    double& operator[](size_t i) {
        if (i >= size_) {
            throw std::out_of_range("Vector index out of bounds");
        }
        return data[i];
    }

    const double& operator[](size_t i) const {
        if (i >= size_) {
            throw std::out_of_range("Vector index out of bounds");
        }
        return data[i];
    }

    Vector operator+(const Vector& other) const {
        if (size_ != other.size()) {
            throw std::invalid_argument("Vector sizes must match for addition");
        }
        Vector result(size_);
        for (size_t i = 0; i < size_; ++i) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
        os << "[";
        for (size_t i = 0; i < v.size(); ++i) {
            os << v.data[i];
            if (i < v.size() - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }
};

#endif // HPC_LINALG_VECTOR_H

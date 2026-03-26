#ifndef HPC_LINALG_VECTOR_H
#define HPC_LINALG_VECTOR_H

#include <vector>
#include <iostream>
#include <numeric>
#include <cmath>
#include <stdexcept>

namespace hpc_linalg {

template <typename T>
class Vector {
public:
    // Constructors
    Vector() = default;
    explicit Vector(size_t size, T initial_value = T{});
    Vector(const std::vector<T>& data);
    Vector(std::initializer_list<T> list);

    // Accessors
    size_t size() const { return data_.size(); }
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    // Vector operations
    T dot(const Vector<T>& other) const;
    T norm() const;
    void normalize();

    // Element-wise operations
    Vector<T> operator+(const Vector<T>& other) const;
    Vector<T> operator-(const Vector<T>& other) const;
    Vector<T> operator*(T scalar) const;
    Vector<T> operator/(T scalar) const;

    // Compound assignment operators
    Vector<T>& operator+=(const Vector<T>& other);
    Vector<T>& operator-=(const Vector<T>& other);
    Vector<T>& operator*=(T scalar);
    Vector<T>& operator/=(T scalar);

    // Comparison
    bool operator==(const Vector<T>& other) const;
    bool operator!=(const Vector<T>& other) const;

    // Stream output
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Vector<U>& vec);

private:
    std::vector<T> data_;
};

// Implementations

template <typename T>
Vector<T>::Vector(size_t size, T initial_value) : data_(size, initial_value) {}

template <typename T>
Vector<T>::Vector(const std::vector<T>& data) : data_(data) {}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> list) : data_(list) {}

template <typename T>
T& Vector<T>::operator[](size_t index) {
    if (index >= data_.size()) {
        throw std::out_of_range("Vector index out of range");
    }
    return data_[index];
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const {
    if (index >= data_.size()) {
        throw std::out_of_range("Vector index out of range");
    }
    return data_[index];
}

template <typename T>
T Vector<T>::dot(const Vector<T>& other) const {
    if (size() != other.size()) {
        throw std::invalid_argument("Vectors must have the same size for dot product");
    }
    return std::inner_product(data_.begin(), data_.end(), other.data_.begin(), T{});
}

template <typename T>
T Vector<T>::norm() const {
    T sum_sq = T{};
    for (const T& val : data_) {
        sum_sq += val * val;
    }
    return std::sqrt(sum_sq);
}

template <typename T>
void Vector<T>::normalize() {
    T vec_norm = norm();
    if (vec_norm == T{}) {
        throw std::runtime_error("Cannot normalize a zero vector");
    }
    for (T& val : data_) {
        val /= vec_norm;
    }
}

template <typename T>
Vector<T> Vector<T>::operator+(const Vector<T>& other) const {
    if (size() != other.size()) {
        throw std::invalid_argument("Vectors must have the same size for addition");
    }
    Vector<T> result(size());
    for (size_t i = 0; i < size(); ++i) {
        result.data_[i] = data_[i] + other.data_[i];
    }
    return result;
}

template <typename T>
Vector<T> Vector<T>::operator-(const Vector<T>& other) const {
    if (size() != other.size()) {
        throw std::invalid_argument("Vectors must have the same size for subtraction");
    }
    Vector<T> result(size());
    for (size_t i = 0; i < size(); ++i) {
        result.data_[i] = data_[i] - other.data_[i];
    }
    return result;
}

template <typename T>
Vector<T> Vector<T>::operator*(T scalar) const {
    Vector<T> result(size());
    for (size_t i = 0; i < size(); ++i) {
        result.data_[i] = data_[i] * scalar;
    }
    return result;
}

template <typename T>
Vector<T> Vector<T>::operator/(T scalar) const {
    if (scalar == T{}) {
        throw std::invalid_argument("Division by zero scalar");
    }
    Vector<T> result(size());
    for (size_t i = 0; i < size(); ++i) {
        result.data_[i] = data_[i] / scalar;
    }
    return result;
}

template <typename T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& other) {
    if (size() != other.size()) {
        throw std::invalid_argument("Vectors must have the same size for addition");
    }
    for (size_t i = 0; i < size(); ++i) {
        data_[i] += other.data_[i];
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator-=(const Vector<T>& other) {
    if (size() != other.size()) {
        throw std::invalid_argument("Vectors must have the same size for subtraction");
    }
    for (size_t i = 0; i < size(); ++i) {
        data_[i] -= other.data_[i];
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator*=(T scalar) {
    for (size_t i = 0; i < size(); ++i) {
        data_[i] *= scalar;
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator/=(T scalar) {
    if (scalar == T{}) {
        throw std::invalid_argument("Division by zero scalar");
    }
    for (size_t i = 0; i < size(); ++i) {
        data_[i] /= scalar;
    }
    return *this;
}

template <typename T>
bool Vector<T>::operator==(const Vector<T>& other) const {
    if (size() != other.size()) {
        return false;
    }
    for (size_t i = 0; i < size(); ++i) {
        if (data_[i] != other.data_[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool Vector<T>::operator!=(const Vector<T>& other) const {
    return !(*this == other);
}

template <typename U>
std::ostream& operator<<(std::ostream& os, const Vector<U>& vec) {
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec.data_[i];
        if (i < vec.size() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

} // namespace hpc_linalg

#endif // HPC_LINALG_VECTOR_H

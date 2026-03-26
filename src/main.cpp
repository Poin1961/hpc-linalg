#include <iostream>
#include "../include/Vector.h"
#include "../include/Matrix.h"

int main() {
    std::cout << "HPC Linear Algebra Library Demo\n";

    // Vector operations
    hpc_linalg::Vector<double> v1 = {1.0, 2.0, 3.0};
    hpc_linalg::Vector<double> v2(3, 1.0);
    hpc_linalg::Vector<double> v3 = {4.0, 5.0, 6.0};

    std::cout << "\nVector v1: " << v1 << std::endl;
    std::cout << "Vector v2: " << v2 << std::endl;
    std::cout << "Vector v3: " << v3 << std::endl;

    // Addition
    hpc_linalg::Vector<double> v_sum = v1 + v3;
    std::cout << "v1 + v3: " << v_sum << std::endl;

    // Dot product
    double dot_product = v1.dot(v3);
    std::cout << "v1 . v3: " << dot_product << std::endl;

    // Norm and normalization
    std::cout << "Norm of v1: " << v1.norm() << std::endl;
    hpc_linalg::Vector<double> v1_normalized = v1;
    v1_normalized.normalize();
    std::cout << "Normalized v1: " << v1_normalized << std::endl;

    // Matrix operations
    hpc_linalg::Matrix<double> m1 = {{1.0, 2.0}, {3.0, 4.0}};
    hpc_linalg::Matrix<double> m2(2, 2, 1.0);
    hpc_linalg::Matrix<double> m3 = {{5.0, 6.0}, {7.0, 8.0}};

    std::cout << "\nMatrix m1:\n" << m1 << std::endl;
    std::cout << "Matrix m2:\n" << m2 << std::endl;
    std::cout << "Matrix m3:\n" << m3 << std::endl;

    // Matrix addition
    hpc_linalg::Matrix<double> m_sum = m1 + m3;
    std::cout << "m1 + m3:\n" << m_sum << std::endl;

    // Matrix multiplication
    hpc_linalg::Matrix<double> m_prod = m1 * m3;
    std::cout << "m1 * m3:\n" << m_prod << std::endl;

    // Matrix-vector multiplication
    hpc_linalg::Vector<double> mv_prod = m1 * v1;
    std::cout << "m1 * v1: " << mv_prod << std::endl;

    // Transpose
    hpc_linalg::Matrix<double> m1_transpose = m1.transpose();
    std::cout << "m1 transpose:\n" << m1_transpose << std::endl;

    return 0;
}

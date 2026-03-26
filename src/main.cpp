#include "../include/Matrix.h"
#include "../include/Vector.h"
#include <iostream>

int main() {
    // Create matrices
    Matrix A(2, 2, {1.0, 2.0, 3.0, 4.0});
    Matrix B(2, 2, {5.0, 6.0, 7.0, 8.0});

    // Matrix multiplication
    Matrix C = A * B;
    std::cout << "Matrix A:\n" << A << std::endl;
    std::cout << "Matrix B:\n" << B << std::endl;
    std::cout << "Matrix C (A * B):\n" << C << std::endl;

    // Vector operations
    Vector v1({1.0, 2.0, 3.0});
    Vector v2({4.0, 5.0, 6.0});
    Vector v_sum = v1 + v2;
    std::cout << "Vector v1: " << v1 << std::endl;
    std::cout << "Vector v2: " << v2 << std::endl;
    std::cout << "Vector sum (v1 + v2): " << v_sum << std::endl;

    return 0;
}

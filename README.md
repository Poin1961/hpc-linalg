# High-Performance Linear Algebra Library (C++)

A high-performance C++ linear algebra library designed for machine learning applications, focusing on optimized matrix operations, vector manipulations, and numerical stability. This library aims to provide a fast and efficient foundation for building custom ML algorithms and accelerating existing ones.

## Features

*   **Optimized Matrix Operations**: Efficient implementations of matrix multiplication, inversion, and decomposition.
*   **Vectorized Computations**: Leverages SIMD instructions for parallel processing of data.
*   **Numerical Stability**: Designed with careful consideration for floating-point arithmetic and error propagation.
*   **Expression Templates**: Reduces temporary object creation for complex operations.
*   **GPU Acceleration (Planned)**: Future integration with CUDA/OpenCL for massively parallel computations.
*   **Easy Integration**: Header-only design for simple inclusion in C++ projects.

## Installation

```bash
git clone https://github.com/Poin1961/hpc-linalg.git
cd hpc-linalg
mkdir build
cd build
cmake ..
make
```

## Usage

```cpp
#include "include/Matrix.h"
#include "include/Vector.h"
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
```

## Project Structure

```
hpc-linalg/
├── include/
│   ├── Matrix.h
│   └── Vector.h
├── src/
│   └── main.cpp
├── CMakeLists.txt
└── README.md
```

## Contributing

Contributions are welcome! Please open an issue or submit a pull request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

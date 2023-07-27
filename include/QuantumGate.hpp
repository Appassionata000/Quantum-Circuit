#ifndef QUANTUMGATE_HPP
#define QUANTUMGATE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <complex>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "Statevector.hpp"

/*
The quantum gate class is a base class for all quantum gates. It contains a 2D array of complex numbers
that represent the quantum gate. The 2D array is stored as a 1D array conventionally.
To access the 2D array, use the following formula for gate(2, 3).
gate(2, 3) = array[(2 - 1) * cols + (3 - 1)].
     0    1     2      3                    (2-1)*4+(3-1) => array[6]
0 ┌  x    x     x      x ┐                            ↓ 
1 |  x    x   (2, 3)   x |  ==> array [ x  x  x  x  x  x  (2, 3) x ....  ]
2 |  x    x     x      x |              0  1  2  3  4  5    6
3 └  x    x     x      x ┘4x4
*/

class QuantumGate
{
public:
    // enum class Type is a scoped enumeration. To access the values, use QuantumGate::Type::Hadamard.
    enum class Type
    {
        Hadamard,
        Swap,
        CNOT,
        PauliX,
        PauliY,
        PauliZ,
        Phase,
        Identity,
        Custom
    };
// The friend function overloads the << operator for the QuantumGate::Type enum class to print the type of the gate.
friend std::ostream &operator<<(std::ostream &os, const QuantumGate::Type &t);
protected:
    /*
    Although the quantum gates are all square matrices, the number of rows and columns are stored separately
    to preserve the characteristics of a matrix.
    */
    size_t rows;
    size_t cols;
    Type type;
    std::unique_ptr<std::complex<double>[]> array;
    
public:
    QuantumGate();      // Default constructor. 
    // Constructor that set all elements to 0 for a given size.
    QuantumGate(size_t size);
    // Constructor that takes the type of the gate, the number of rows and columns, and a list of complex numbers.
    QuantumGate(Type, const size_t, std::initializer_list<std::complex<double>>);
    // The smart pointer will handle the memory so the destructor can be empty.
    ~QuantumGate() {}

    QuantumGate(const QuantumGate &q);            // copy constructor
    QuantumGate &operator=(const QuantumGate &q); // copy assignment operator
    QuantumGate(QuantumGate &&q);                 // move constructor
    QuantumGate &operator=(QuantumGate &&q);      // move assignment operator

    /*
    Pverloads the () operator to access the 2D array.
    The fisrt version allows modification of the elements.
    The second version does not allow modification of the elements.
    */ 
    std::complex<double> &operator()(size_t row, size_t col);
    const std::complex<double> &operator()(size_t row, size_t col) const;

    // Overloads the +, -, and * operators following the rules of matrix addition, subtraction, and multiplication.
    // lvalue version
    QuantumGate operator+(const QuantumGate &q) const;
    QuantumGate operator-(const QuantumGate &q) const;
    QuantumGate operator*(const QuantumGate &q) const;
    QuantumGate operator*(const std::complex<double> &c) const;
    QuantumGate kronecker(const QuantumGate &q) const;

    // rvalue version
    QuantumGate operator+(QuantumGate &&q) const;
    QuantumGate operator-(QuantumGate &&q) const;
    QuantumGate operator*(QuantumGate &&q) const;

    // compound assignment operators
    QuantumGate& operator+=(const QuantumGate &q);
    QuantumGate& operator-=(const QuantumGate &q);

    // getters and setters
    inline void set_type(Type type) { this->type = type; }
    inline Type get_type() const   { return type; }
    inline size_t get_rows() const { return rows; }
    inline size_t get_cols() const { return cols; }
    inline size_t size() const { return rows * cols; }

    // Format the 2D array as a matrix and return a vector of strings.
    // Requires "Formap.hpp"
    std::vector<std::string> to_string();
    std::vector<size_t> get_max_width();
    // display the 2D array as a matrix
    void display_matrix();
    void round();

    // pre-defined quantum gates
    static QuantumGate PauliX;
    static QuantumGate PauliY;
    static QuantumGate PauliZ;
    static QuantumGate Hadamard2x2;
    static QuantumGate Identity2x2;
    static QuantumGate CNOT4x4;
    static QuantumGate SWAP4x4;

    /*
    Significantly small number may arise when doing std::exp(std::complex<double>).
    If the result is small than ROUND_MINIMUM, it is then set to 0.
    */
    const double ROUND_MINIMUM = 1e-10;
};


// Return the Dyadic product of two statevectors. 
QuantumGate dyad(Statevector &v1, Statevector &v2);

// Rerturn the product of a quantum gate and a statevector.
Statevector operator*(QuantumGate &q, Statevector &v);

// Return an identity matrix of given size n.
QuantumGate Identity(size_t n);

// Return a zero matrix of given size n.
QuantumGate Zeros(size_t n);

#endif
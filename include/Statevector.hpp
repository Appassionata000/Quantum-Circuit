#ifndef Statevector_HPP
#define Statevector_HPP

#include "Format.hpp"
#include <map>
#include <memory>
#include <random>

/**
 * Statevector.hpp
 * This file contains the declaration of the Statevector class and related functions.
 *
 * The Statevector class is designed to represent the quantum state of a system of qubits. 
 *
 * The class includes constructors to initialize the statevector with a specific number of qubits, 
 * with a list of qubit states, or with a list of complex number elements.
 *
 * Additionally, the class defines a set of operators to perform algebraic operations on statevectors, 
 * as well as to access individual amplitudes in the statevector. The size and number of qubits of the 
 * statevector can also be retrieved.
 *
 * The Statevector class also includes methods to display the statevector in row or column format, 
 * to round the amplitudes to a certain precision, and to get the maximum width of the amplitudes 
 * for formatting purposes.
 *
 * The file also includes a function to generate a standard basis for a given number of qubits, 
 * a function to generate a specific state for a given number of qubits, and a function to display 
 * the standard basis for a given number of qubits.
 */

class Statevector
{
private:
    size_t qubit_n;
    std::unique_ptr<std::complex<double>[]> array;

public:
    Statevector();
    Statevector(size_t qubit_n_);
    Statevector(std::initializer_list<int> qubit_states);
    Statevector(std::initializer_list<std::complex<double>> elements);

    Statevector(const Statevector &s);            // copy constructor
    Statevector &operator=(const Statevector &s); // copy assignment operator
    Statevector(Statevector &&s);                 // move constructor
    Statevector &operator=(Statevector &&s);      // move assignment operator

    Statevector operator+(const Statevector &s);
    Statevector operator-(const Statevector &s);
    Statevector operator/(const std::complex<double> &c);
    std::complex<double> &operator[](size_t i);
    const std::complex<double> &operator[](size_t i) const;

    size_t qubit_num() const { return qubit_n; }
    size_t size() { return pow(2, qubit_n); }

    size_t get_max_width() const;
    void display_row();
    void display_column();
    
    void round();
};

// Generate a map of standard basis states for a given number of qubits
std::map<std::string, Statevector> generate_std_basis(size_t qubit_n);

// Generate a specific state for a given number of qubits
Statevector generate_state(size_t qubit_n, std::string state_kind, std::string state_str="");

// Auxiliary function. Display the standard basis for a given number of qubits
void display_std_basis(size_t qubit_n);

#endif // Statevector_HPP

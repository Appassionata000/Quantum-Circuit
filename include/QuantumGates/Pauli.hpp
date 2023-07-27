#ifndef PAULI_HPP
#define PAULI_HPP

#include "../QuantumGate.hpp"

/*
The Pauli class, derived class of QuantumGate
The object has an attribute pauli_type, which is either "X", "Y", or "Z".
*/

class Pauli : public QuantumGate
{
private:
    std::string pauli_type;
public:
    Pauli();
    Pauli(size_t qubit_n_, size_t qubit_eff_, std::string pauli_type_);
    Pauli(size_t qubit_n_, std::initializer_list<size_t> qubit_eff_list_, std::string pauli_type_);
    ~Pauli() {}

    std::string get_type() const { return pauli_type; }
};



#endif
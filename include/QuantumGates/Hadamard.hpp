#ifndef HADAMARD_HPP
#define HADAMARD_HPP

#include "../QuantumGate.hpp"

/*
The Hadamard class, which is a derived class of the QuantumGate class.
The Hadamard gate is a 2x2 gate that acts on a single qubit.
The Hadamard gate is defined as:
H = 1/sqrt(2) * [1,  1, 
                 1, -1].

When used for adding a gate to a QuantumCircuit, the object is created for the number of qubits in the circuit.
The effective gate is a result of kronecker products of the Hadamard gate and the identity gate.
*/

class Hadamard : public QuantumGate
{
public:
    Hadamard();
    Hadamard(size_t qubit_n_);
    Hadamard(size_t qubit_n_, size_t qubit_eff_);
    Hadamard(size_t qubit_n_, std::initializer_list<size_t> qubits_eff_list_);
    ~Hadamard() {}
};

#endif
#include "../../include/QuantumGates/Hadamard.hpp"

// Default constructor, creates a 2x2 Hadamard gate.
Hadamard::Hadamard()
{
    QuantumGate{QuantumGate::Hadamard2x2};
    type = Type::Hadamard;
}

// Creates a Hadamard gate of size 2^n x 2^n, which is the kronecker product of n 2x2 Hadamard gates.
Hadamard::Hadamard(size_t qubit_n_) : QuantumGate{Zeros(qubit_n_)}
{
    QuantumGate res{QuantumGate::Hadamard2x2};
    for (int i = 0; i < qubit_n_ - 1; i++)
    {
        res = res.kronecker(QuantumGate::Hadamard2x2);
    }
    QuantumGate::operator=(res);
    type = Type::Hadamard;
}

// Creates a Quantum gate for n qubits, with the Hadamard gate applied to the qubit at position qubit_eff.
Hadamard::Hadamard(size_t qubit_n_, size_t qubit_eff_)
{
    /*
    If the gate is applied to the first qubit, the effective gate is H ⊗ I ⊗ I ⊗ ... ⊗ I
    If the gate is applied to a qubit other than the first one, the effective gate is I ⊗ ... ⊗ H ⊗ ... ⊗ I
    */
    QuantumGate res{qubit_eff_ == 0 ? QuantumGate::Hadamard2x2 : QuantumGate::Identity2x2};
    for (int i = 1; i < qubit_n_; i++)
    {
        if (i == qubit_eff_)
            res = res.kronecker(QuantumGate::Hadamard2x2);
        else
            res = res.kronecker(QuantumGate::Identity2x2);
    }
    QuantumGate::operator=(res);
    type = Type::Hadamard;
}

// Creates a quantum gate for n qubits, with the Hadamard gate applied to the qubits at positions qubits_eff_list.
Hadamard::Hadamard(size_t qubit_n_, std::initializer_list<size_t> qubits_eff_list_) : 
QuantumGate{Zeros(qubit_n_)}
{
    std::vector<size_t> qubits_eff_list{qubits_eff_list_};
    QuantumGate res{qubits_eff_list.at(0) == 0 ? QuantumGate::Hadamard2x2 : QuantumGate::Identity2x2};

    for (size_t i = 1; i < qubit_n_; i++)
    {   
        if (std::find(qubits_eff_list.begin(), qubits_eff_list.end(), i) != qubits_eff_list.end())
        {
            res = res.kronecker(QuantumGate::Hadamard2x2);
        }
        else
        {
            res = res.kronecker(QuantumGate::Identity2x2);
        }
    }
    QuantumGate::operator=(res);
    type = Type::Hadamard;
}

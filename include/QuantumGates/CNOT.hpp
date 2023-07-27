#ifndef CNOT_HPP
#define CNOT_HPP

#include "../QuantumGate.hpp"

class CNOT : public QuantumGate
{
private:
    size_t qubits;
    size_t control_qubit;
    size_t target_qubit;
public:
    CNOT();
    CNOT(size_t qubits_, size_t control_qubit_, size_t target_qubit_);
    ~CNOT() {}
};




#endif // CNOT_HPP
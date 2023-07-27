#include "../../include/QuantumGates/CNOT.hpp"

CNOT::CNOT()
{
    QuantumGate{QuantumGate::CNOT4x4};
    qubits = 2;
    control_qubit = 0;
    target_qubit = 1;
}

CNOT::CNOT(size_t qubits_, size_t control_qubit_, size_t target_qubit_)
    : QuantumGate(Zeros(qubits_)), qubits(qubits_), control_qubit(control_qubit_), target_qubit(target_qubit_)
{
    auto basis = generate_std_basis(qubits);
    QuantumGate res = Zeros(qubits);

    for (auto it = basis.begin(); it != basis.end(); it++)
    {
        if (it->first.at(control_qubit) == '1')
        {
            std::string temp = it->first;
            temp.at(target_qubit) = (temp.at(target_qubit) == '0') ? '1' : '0';
            res = res + dyad(basis[it->first], basis[temp]);
        }
        else
        {
            res = res + dyad(basis[it->first], basis[it->first]);
        }
    }
    QuantumGate::operator=(res);
    this->set_type(Type::CNOT);
}

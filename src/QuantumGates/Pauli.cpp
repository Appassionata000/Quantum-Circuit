#include "../../include/QuantumGates/Pauli.hpp"

Pauli::Pauli()
{
    QuantumGate{QuantumGate::Identity2x2};
    pauli_type = "I";
}

Pauli::Pauli(size_t qubit_n_, size_t qubit_eff_, std::string pauli_type_) : pauli_type(pauli_type_), QuantumGate{Zeros(qubit_n_)}
{
    QuantumGate res{qubit_eff_ == 0 ? QuantumGate::PauliX : QuantumGate::Identity2x2};

    if (pauli_type == "X")
        res = QuantumGate::PauliX;
    else if (pauli_type == "Y")
        res = QuantumGate::PauliY;
    else if (pauli_type == "Z")
        res = QuantumGate::PauliZ;
    else
        res = QuantumGate::Identity2x2;

    for (int i = 1; i < qubit_n_; i++)
    {
        if (i == qubit_eff_)
            res = res.kronecker(QuantumGate::PauliX);
        else
            res = res.kronecker(QuantumGate::Identity2x2);
    }
    QuantumGate::operator=(res);

    if (pauli_type == "X")
        this->set_type(QuantumGate::Type::PauliX);
    else if (pauli_type == "Y")
        this->set_type(QuantumGate::Type::PauliY);
    else if (pauli_type == "Z")
        this->set_type(QuantumGate::Type::PauliZ);
    else
        this->set_type(QuantumGate::Type::Identity);
}

Pauli::Pauli(size_t qubit_n_, std::initializer_list<size_t> qubit_eff_list_, std::string pauli_type_) : pauli_type(pauli_type_), QuantumGate{Zeros(qubit_n_)}
{
    QuantumGate res = QuantumGate::Identity2x2;
    std::vector<size_t> qubits_eff_list{qubit_eff_list_};

    if (qubits_eff_list.at(0) == 0)
    {
        if (pauli_type == "X")
            res = QuantumGate::PauliX;
        else if (pauli_type == "Y")
            res = QuantumGate::PauliY;
        else if (pauli_type == "Z")
            res = QuantumGate::PauliZ;
        else
            res = QuantumGate::Identity2x2;
    }
    else
        res = QuantumGate::Identity2x2;

    for (size_t i = 1; i < qubit_n_; i++)
    {
        if (std::find(qubits_eff_list.begin(), qubits_eff_list.end(), i) != qubits_eff_list.end())
        {
            if (pauli_type == "X")
                res = res.kronecker(QuantumGate::PauliX);
            else if (pauli_type == "Y")
                res = res.kronecker(QuantumGate::PauliY);
            else if (pauli_type == "Z")
                res = res.kronecker(QuantumGate::PauliZ);
            else
                res = res.kronecker(QuantumGate::Identity2x2);
        }
        else
            res = res.kronecker(QuantumGate::Identity2x2);
    }
    QuantumGate::operator=(res);

    if (pauli_type == "X")
        this->set_type(QuantumGate::Type::PauliX);
    else if (pauli_type == "Y")
        this->set_type(QuantumGate::Type::PauliY);
    else if (pauli_type == "Z")
        this->set_type(QuantumGate::Type::PauliZ);
    else
        this->set_type(QuantumGate::Type::Identity);
}
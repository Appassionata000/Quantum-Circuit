#include "../../include/QuantumGates/Phase.hpp"

Phase::Phase()
{
    this->set_type(Type::Phase);

    QuantumGate{QuantumGate::Identity2x2};
    phase = 0;
}


Phase::Phase(size_t qubit_n_, size_t qubit_eff_, double phase_) :
phase(phase_), QuantumGate{Zeros(qubit_n_)}
{  
    QuantumGate res{QuantumGate::Identity2x2};
    QuantumGate Phase2x2{Type::Phase, 2, {1, 0, 0, std::exp(std::complex<double>(0, phase))}};

    if (qubit_eff_ == 0)
    {
        res(2, 2) = std::exp(std::complex<double>(0, phase));
        QuantumGate::operator=(res);
        this->set_type(Type::Phase);
        return;
    }
    for (int i = 1; i < qubit_n_; i++)
    {
        if (i == qubit_eff_)
            res = res.kronecker(Phase2x2);
        else
            res = res.kronecker(QuantumGate::Identity2x2);
    }

    QuantumGate::operator=(res);
    this->set_type(Type::Phase);
}
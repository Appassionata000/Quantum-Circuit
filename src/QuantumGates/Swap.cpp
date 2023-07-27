#include "../../include/QuantumGates/Swap.hpp"

Swap::Swap()
{
    this->set_type(Type::Swap);
    QuantumGate{QuantumGate::SWAP4x4};
    swap_q1 = 0;
    swap_q2 = 1;
}

Swap::Swap(size_t qubit_n_, size_t swap_q1_, size_t swap_q2_)
    : QuantumGate(Zeros(qubit_n_)), swap_q1(swap_q1_), swap_q2(swap_q2_)
{
    auto basis = generate_std_basis(qubit_n_);
    QuantumGate res = Zeros(qubit_n_);

    for (auto it = basis.begin(); it != basis.end(); it++)
    {
        if (it->first.at(swap_q1) == it->first.at(swap_q2))
        {
            res = res + dyad(basis[it->first], basis[it->first]);
        }
        else
        {
            std::string temp = it->first;
            temp.at(swap_q1) = it->first.at(swap_q2);
            temp.at(swap_q2) = it->first.at(swap_q1);
            res = res + dyad(basis[it->first], basis[temp]);
        }
    }
    QuantumGate::operator=(res);
    this->set_type(Type::Swap);
}
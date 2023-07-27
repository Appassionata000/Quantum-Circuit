#ifndef SWAP_HPP
#define SWAP_HPP

#include "../QuantumGate.hpp"

/*
The Swap class, derived class of QuantumGate
The object has two attributes swap_q1 and swap_q2, which are the qubits to be swapped.
*/

class Swap : public QuantumGate
{
private:
    size_t swap_q1;
    size_t swap_q2;
public:
    Swap();
    Swap(size_t qubit_n_, size_t swap_q1_, size_t swap_q2_);
    ~Swap() {}
};



#endif
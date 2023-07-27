#ifndef PHASE_HPP
#define PHASE_HPP

#include "../QuantumGate.hpp"

/*
The phase gate class, derived class of QuantumGate
The object has an attribute phase.
*/

class Phase : public QuantumGate
{
private:
    double phase;
public:
    Phase();
    Phase(size_t qubit_n_, size_t qubit_eff_, double phase_);
    ~Phase() {}

    double get_phase() const { return phase; }
};




#endif
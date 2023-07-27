#ifndef QUANTUMCIRCUIT_HPP
#define QUANTUMCIRCUIT_HPP

#include "Statevector.hpp"
#include "QuantumGate.hpp"
#include "QuantumGates/Hadamard.hpp"
#include "QuantumGates/Swap.hpp"
#include "QuantumGates/CNOT.hpp"
#include "QuantumGates/Pauli.hpp"
#include "QuantumGates/Phase.hpp"
#include <utility>
#include <algorithm>


/*
The following defines some essential elements to draw a quantum circuit.
Below is an example of a quantum circuit with 3 qubits and 3 gates.

    ┌───┐               ──> upper line   ┐
0 ──│ H │────•───────  ──> middel line  │──> circuitLine ──┐
    └───┘    │          ──> bottom line  ┘                   │
             │                                                │
1 ───────────⊕────•──                        circuitLine   │───> std::vector<circuitLine>
                  │                                           │
                  │                                           │
2 ────────────────⊕──                        circuitLine ──┘

The basic components of a quantum circuit the struct circuitLine which contains 3 strings.
The middel string contains the wires and the gates.
The upper and bootom strings include the compelementary symbols to the gate, and most of the 
elemnts are spaces.
*/

struct circuitLine
{
    std::string upper {""};
    std::string middle {""};
    std::string bottom {""};
};

namespace CIRCUIT_SYMBOLS
{
    const std::string WIRE{"─"};
    const std::string SPACE{" "};
    const std::string CONTROL{"•"};
    const std::string TARGET{"⊕"};
    const std::string SWAP{"x"};
    const std::string VERTICAL{"│"};
    const std::string BOX_TOP   {"┌───┐"};
    const std::string BOX_MIDDLE{"│   │"};
    const std::string BOX_BOTTOM{"└───┘"};
    const std::string BOX_MIDDLE_H{"│ H │"};
    const std::string BOX_MIDDLE_PX{"│P_X│"};
    const std::string BOX_MIDDLE_PY{"│P_Y│"};
    const std::string BOX_MIDDLE_PZ{"│P_Z│"};
    const std::string BOX_MIDDLE_PHASE{"│Phi│"};
    const std::string BOX_MIDDLE_PHASE_180{"│ π │"};
    const std::string BOX_MIDDLE_PHASE_90{"│π/2│"};
    const std::string BOX_MIDDLE_PHASE_45{"│π/4│"};
};

// The following functions are used to draw a quantum circuit.
void print_circuitLine(circuitLine line);

void add_wire(circuitLine &line, size_t length);

void add_wire(std::vector<circuitLine> &lines, size_t length);

/*
The first element of the pair is a vector of size_t that contains the qubits that the gate acts on.
The second element is the gate. 
For example, if the Hadamard gate H acts on qubit 0, the pair will be {0, H}.
If the CNOT gate acts on qubit 0 and 1, the pair will be {{0, 1}, CNOT}.
If many Hadamard gates act on several qubits parallelly, the pair can be {{0, 1, 2, 3}, H}.
*/ 
using GatesWithTarget = std::pair<std::vector<size_t>, QuantumGate>;

/*
The QuantumCircuit class is used to store the gates and the targets.
The QuantumCircuit object is initialized with the number of qubits, and the gates and targets are added later.
The friend function evolve() is used to return the statevector after the circuit is applied to it.
The Hadamard gates are allowed to be added parallely to save spaces.

Example of usage:
>>QuantumGate qc(3);
>>qc.add_Hadamard(0);
>>qc.add_CNOT(0, 1);
>>qc.display_circuit();
>>Statevector initial_state{0, 1, 0};
>>Statevector final_state = evolve(state, qc);
*/

class QuantumCircuit
{
friend Statevector evolve(Statevector &state, QuantumCircuit &circuit, std::string show_step);
private:
    size_t qubit_n;
    std::vector<GatesWithTarget> gates_targets;
    std::string info{""};
public:
    QuantumCircuit();
    QuantumCircuit(size_t qubit_n_);
    ~QuantumCircuit() {}

    void add_Hadamard(size_t q);
    void add_Hadamard(std::initializer_list<size_t> qubit_eff_list);
    void add_Swap(size_t q1, size_t q2);
    void add_CNOT(size_t q1, size_t q2);
    void add_Pauli(size_t q, std::string pauli_type);
    void add_Phase(size_t q, double phase);
    
    void show_gate_list() const;
    void display_circuit();
};


#endif
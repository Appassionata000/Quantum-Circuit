#include "../include/QuantumCircuit.hpp"

// Default constructor
QuantumCircuit::QuantumCircuit()
{
    qubit_n = 1;
}

// Parameterized constructor. The attribute Gates_targets is initialized as an empty vector.
QuantumCircuit::QuantumCircuit(size_t qubit_n_)
{
    qubit_n = qubit_n_;
}

// Method to add a Hadamard gate to a single qubit
void QuantumCircuit::add_Hadamard(size_t q)
{
    std::vector<size_t> qubit_eff{q};
    gates_targets.push_back({qubit_eff, Hadamard{qubit_n, q}});
}

// Method to add a Hadamard gate to multiple qubits parallelly
void QuantumCircuit::add_Hadamard(std::initializer_list<size_t> qubit_eff_list)
{
    std::vector<size_t> qubit_eff{qubit_eff_list};
    gates_targets.push_back({qubit_eff, Hadamard{qubit_n, qubit_eff_list}});
}

// Method to add a Swap gate to two qubits
void QuantumCircuit::add_Swap(size_t q1, size_t q2)
{
    std::vector<size_t> qubit_eff{q1, q2};
    gates_targets.push_back({qubit_eff, Swap{qubit_n, q1, q2}});
}

// Method to add a CNOT gate to two qubits
void QuantumCircuit::add_CNOT(size_t q1, size_t q2)
{
    std::vector<size_t> qubit_eff{q1, q2};
    gates_targets.push_back({qubit_eff, CNOT{qubit_n, q1, q2}});
}

// Method to add a Pauli gate to a single qubit
void QuantumCircuit::add_Pauli(size_t q, std::string pauli_type)
{
    std::vector<size_t> qubit_eff{q};
    gates_targets.push_back({qubit_eff, Pauli{qubit_n, q, pauli_type}});
}

// Method to add a Phase gate to a single qubit
void QuantumCircuit::add_Phase(size_t q, double phase)
{
    std::vector<size_t> qubit_eff{q};
    gates_targets.push_back({qubit_eff, Phase{qubit_n, q, phase}});
}

// Friend function to evolve a statevector with a quantum circuit
Statevector evolve(Statevector &state, QuantumCircuit &circuit, std::string show_step)
{
    Statevector final_state = state;

    int i = 1;
    for (auto it = circuit.gates_targets.begin(); it != circuit.gates_targets.end(); it++, i++)
    {
        // Decompose the pair
        std::vector<size_t> qubit_eff = it->first;
        QuantumGate gate = it->second;

        if (show_step == "all")
        {
            std::cout << "[Step " << i << "]  " << std::endl;
            std::cout << "Gate: " << std::endl;
            gate.display_matrix();

            final_state = gate * final_state;

            std::cout << "Current state: " << std::endl;
            final_state.display_row();

            std::cout << std::endl;
        }
        else 
        {
            final_state = gate * final_state;
        }
    }

    return final_state;
}

void add_wire(circuitLine &line, size_t length)
{
    for (int i = 0; i < length; i++)
    {
        line.upper += CIRCUIT_SYMBOLS::SPACE;
        line.middle += CIRCUIT_SYMBOLS::WIRE;
        line.bottom += CIRCUIT_SYMBOLS::SPACE;
    }
}

void add_wire(std::vector<circuitLine> &lines, size_t length)
{
    for (auto it = lines.begin(); it != lines.end(); it++)
    {
        for (int i = 0; i < length; i++)
        {
            it->upper += CIRCUIT_SYMBOLS::SPACE;
            it->middle += CIRCUIT_SYMBOLS::WIRE;
            it->bottom += CIRCUIT_SYMBOLS::SPACE;
        }
    }
}

void add_qubit_number(std::vector<circuitLine> &lines, size_t qubit_n)
{
    int i = 0;
    bool ADDITIONAL_SPACE = false;
    for (auto it = lines.begin(); it != lines.end(); it++, i++)
    {
        it->upper += CIRCUIT_SYMBOLS::SPACE;
        it->middle += std::to_string(i);
        it->bottom += CIRCUIT_SYMBOLS::SPACE;

        it->upper += CIRCUIT_SYMBOLS::SPACE;
        it->middle += CIRCUIT_SYMBOLS::SPACE;
        it->bottom += CIRCUIT_SYMBOLS::SPACE;

        if (i > 9)
        {
            ADDITIONAL_SPACE = true;
        }
    }
    if (ADDITIONAL_SPACE)
    {
        int i = 0;
        for (auto it = lines.begin(); it != lines.end(); it++, i++)
        {
            if (i <= 9)
            {
                it->upper += CIRCUIT_SYMBOLS::SPACE;
                it->middle += CIRCUIT_SYMBOLS::SPACE;
                it->bottom += CIRCUIT_SYMBOLS::SPACE;
            }
        }
    }
}

void print_circuitLine(circuitLine line)
{
    std::cout << line.upper << std::endl;
    std::cout << line.middle << std::endl;
    std::cout << line.bottom << std::endl;
}

void QuantumCircuit::display_circuit()
{
    std::vector<circuitLine> circuit_lines;

    // Initialize n qubit lines parallel to each other
    for (int i = 0; i < qubit_n; i++)
    {
        circuitLine line;
        circuit_lines.push_back(line);
    }

    add_qubit_number(circuit_lines, qubit_n);

    /*
        gates_targets example:
        {0} Hadamard,
        {1} Hadamard,
        {0, 2} Swap
        The order of gates_targets is the order of gates in the circuit from left to right
    */
    for (auto it = gates_targets.begin(); it != gates_targets.end(); it++)
    {
        std::vector<size_t> qubit_eff = it->first;
        QuantumGate gate = it->second;

        // Add wire at the beginning of each gate
        add_wire(circuit_lines, 2);

        if (gate.get_type() == QuantumGate::Type::Hadamard)
        {
            if (qubit_eff.size() == 1)
            {
                circuit_lines[qubit_eff[0]].upper += CIRCUIT_SYMBOLS::BOX_TOP;
                circuit_lines[qubit_eff[0]].middle += CIRCUIT_SYMBOLS::BOX_MIDDLE_H;
                circuit_lines[qubit_eff[0]].bottom += CIRCUIT_SYMBOLS::BOX_BOTTOM;

                for (int i = 0; i < qubit_n; i++)
                {
                    if (i != qubit_eff[0])
                    {
                        // Add wire at other qubit lines
                        add_wire(circuit_lines[i], 5);
                    }
                }
            }
            // e.g. {0, 1, 2} Hadamard
            else
            {
                for (int i = 0; i < qubit_n; i++)
                {
                    if (std::find(qubit_eff.begin(), qubit_eff.end(), i) != qubit_eff.end())
                    {
                        circuit_lines[i].upper += CIRCUIT_SYMBOLS::BOX_TOP;
                        circuit_lines[i].middle += CIRCUIT_SYMBOLS::BOX_MIDDLE_H;
                        circuit_lines[i].bottom += CIRCUIT_SYMBOLS::BOX_BOTTOM;
                    }
                    else
                    {
                        // Add wire at other qubit lines
                        add_wire(circuit_lines[i], 5);
                    }
                }
            }
        }
        /*
        Maximum 4 Steps for quibit_eff[1] - qubit_eff[0] = 1:
        1. Draw controlled and target symbol on corres. qubit.
        2. Draw vertical line below the controlled qubit.
        3. Draw vertical line above the target qubit.
        4. None
        5. Draw wire at other qubits

        Maximum 5 Steps for quibit_eff[1] - qubit_eff[0] > 1:
        1. Draw controlled and target symbol on corres. qubit.
        2. Draw vertical line below the controlled qubit.
        3. Draw vertical line above the target qubit
        4. Draw vertical lines between controlled and target qubit
        5. Draw wire at other qubits

        qubit_eff[0] is the controlled qubit
        qubit_eff[1] is the target qubit
        */
        if (gate.get_type() == QuantumGate::Type::CNOT)
        {
            // e.g. {0, 2} CNOT or {0, 4} CNOT
            if (qubit_eff[0] < qubit_eff[1])
            {
                // Step 1: Draw symbols at qubit_eff[0] and qubit_eff[1]
                // Step 2: Draw vertical line below controlled qubit
                // Step 3: Draw vertical line above target qubit
                circuit_lines[qubit_eff[0]].upper += CIRCUIT_SYMBOLS::SPACE;
                circuit_lines[qubit_eff[0]].middle += CIRCUIT_SYMBOLS::CONTROL;
                circuit_lines[qubit_eff[0]].bottom += CIRCUIT_SYMBOLS::VERTICAL;

                circuit_lines[qubit_eff[1]].upper += CIRCUIT_SYMBOLS::VERTICAL;
                circuit_lines[qubit_eff[1]].middle += CIRCUIT_SYMBOLS::TARGET;
                circuit_lines[qubit_eff[1]].bottom += CIRCUIT_SYMBOLS::SPACE;

                // Step 4: Draw additional vertical lines between qubit_eff[0] and qubit_eff[1]
                if (qubit_eff[1] - qubit_eff[0] > 1)
                {
                    for (int i = qubit_eff[0] + 1; i < qubit_eff[1]; i++)
                    {
                        circuit_lines[i].upper += CIRCUIT_SYMBOLS::VERTICAL;
                        circuit_lines[i].middle += CIRCUIT_SYMBOLS::VERTICAL;
                        circuit_lines[i].bottom += CIRCUIT_SYMBOLS::VERTICAL;
                    }
                    // Step 5: Add wire at other qubit lines
                    for (int i = 0; i < qubit_n; i++)
                    {
                        if (i < qubit_eff[0] || i > qubit_eff[1])
                        {
                            add_wire(circuit_lines[i], 1);
                        }
                    }
                }
                else
                {
                    // Step 5: Add wire at other qubit lines
                    for (int i = 0; i < qubit_n; i++)
                    {
                        if (i != qubit_eff[0] && i != qubit_eff[1])
                        {
                            add_wire(circuit_lines[i], 1);
                        }
                    }
                }
            }
            // e.g. {2, 0} CNOT. qubit_eff[0] = 2, qubit_eff[1] = 0
            else if (qubit_eff[0] > qubit_eff[1])
            {
                // Draw symbols at qubit_eff[0] and qubit_eff[1]
                circuit_lines[qubit_eff[1]].upper += CIRCUIT_SYMBOLS::SPACE;
                circuit_lines[qubit_eff[1]].middle += CIRCUIT_SYMBOLS::TARGET;
                circuit_lines[qubit_eff[1]].bottom += CIRCUIT_SYMBOLS::VERTICAL;

                circuit_lines[qubit_eff[0]].upper += CIRCUIT_SYMBOLS::VERTICAL;
                circuit_lines[qubit_eff[0]].middle += CIRCUIT_SYMBOLS::CONTROL;
                circuit_lines[qubit_eff[0]].bottom += CIRCUIT_SYMBOLS::SPACE;

                // Draw additional vertical lines between qubit_eff[0] and qubit_eff[1]
                if (qubit_eff[0] - qubit_eff[1] > 1)
                {
                    for (int i = qubit_eff[1] + 1; i < qubit_eff[0]; i++)
                    {
                        circuit_lines[i].upper += CIRCUIT_SYMBOLS::VERTICAL;
                        circuit_lines[i].middle += CIRCUIT_SYMBOLS::VERTICAL;
                        circuit_lines[i].bottom += CIRCUIT_SYMBOLS::VERTICAL;
                    }
                    // Add wire at other qubit lines
                    for (int i = 0; i < qubit_n; i++)
                    {
                        if (i < qubit_eff[1] || i > qubit_eff[0])
                        {
                            add_wire(circuit_lines[i], 1);
                        }
                    }
                }
                else
                {
                    // Add wire at other qubit lines
                    for (int i = 0; i < qubit_n; i++)
                    {
                        if (i != qubit_eff[0] && i != qubit_eff[1])
                        {
                            add_wire(circuit_lines[i], 1);
                        }
                    }
                }
            }
            else
            {
                std::cerr << "Error: Invalid CNOT gate." << std::endl;
            }
        }

        if (gate.get_type() == QuantumGate::Type::Swap)
        {
            // e.g. {0, 2} Swap
            // 0 is qubit_above, 2 is qubit_below
            size_t qubit_above = qubit_eff[0] > qubit_eff[1] ? qubit_eff[1] : qubit_eff[0];
            size_t qubit_below = qubit_eff[0] > qubit_eff[1] ? qubit_eff[0] : qubit_eff[1];

            circuit_lines[qubit_above].upper += CIRCUIT_SYMBOLS::SPACE;
            circuit_lines[qubit_above].middle += CIRCUIT_SYMBOLS::SWAP;
            circuit_lines[qubit_above].bottom += CIRCUIT_SYMBOLS::VERTICAL;

            circuit_lines[qubit_below].upper += CIRCUIT_SYMBOLS::VERTICAL;
            circuit_lines[qubit_below].middle += CIRCUIT_SYMBOLS::SWAP;
            circuit_lines[qubit_below].bottom += CIRCUIT_SYMBOLS::SPACE;

            if (qubit_below - qubit_above > 1)
            {
                for (int i = qubit_above + 1; i < qubit_below; i++)
                {
                    circuit_lines[i].upper += CIRCUIT_SYMBOLS::VERTICAL;
                    circuit_lines[i].middle += CIRCUIT_SYMBOLS::VERTICAL;
                    circuit_lines[i].bottom += CIRCUIT_SYMBOLS::VERTICAL;
                }
                for (int i = 0; i < qubit_n; i++)
                {
                    if (i < qubit_above || i > qubit_below)
                    {
                        add_wire(circuit_lines[i], 1);
                    }
                }
            }
            else
            {
                for (int i = 0; i < qubit_n; i++)
                {
                    if (i != qubit_above && i != qubit_below)
                    {
                        add_wire(circuit_lines[i], 1);
                    }
                }
            }
        }

        if (gate.get_type() == QuantumGate::Type::PauliX ||
            gate.get_type() == QuantumGate::Type::PauliY ||
            gate.get_type() == QuantumGate::Type::PauliZ)
        {
            if (qubit_eff.size() == 1)
            {
                circuit_lines[qubit_eff[0]].upper += CIRCUIT_SYMBOLS::BOX_TOP;

                if (gate.get_type() == QuantumGate::Type::PauliX)
                    circuit_lines[qubit_eff[0]].middle += CIRCUIT_SYMBOLS::BOX_MIDDLE_PX;
                else if (gate.get_type() == QuantumGate::Type::PauliY)
                    circuit_lines[qubit_eff[0]].middle += CIRCUIT_SYMBOLS::BOX_MIDDLE_PY;
                else if (gate.get_type() == QuantumGate::Type::PauliZ)
                    circuit_lines[qubit_eff[0]].middle += CIRCUIT_SYMBOLS::BOX_MIDDLE_PZ;

                circuit_lines[qubit_eff[0]].bottom += CIRCUIT_SYMBOLS::BOX_BOTTOM;

                for (int i = 0; i < qubit_n; i++)
                {
                    if (i != qubit_eff[0])
                    {
                        add_wire(circuit_lines[i], 5);
                    }
                }
            }
            else
            {
                ;
            }
        }

        if (gate.get_type() == QuantumGate::Type::Phase)
        {
            circuit_lines[qubit_eff[0]].upper += CIRCUIT_SYMBOLS::BOX_TOP;
            circuit_lines[qubit_eff[0]].middle += CIRCUIT_SYMBOLS::BOX_MIDDLE_PHASE;
            circuit_lines[qubit_eff[0]].bottom += CIRCUIT_SYMBOLS::BOX_BOTTOM;

            for (int i = 0; i < qubit_n; i++)
            {
                if (i != qubit_eff[0])
                {
                    add_wire(circuit_lines[i], 5);
                }
            }
        }
        // Add wire at the end of each gate
        add_wire(circuit_lines, 2);
    }

    for (auto it = circuit_lines.begin(); it != circuit_lines.end(); it++)
    {
        print_circuitLine(*it);
    }
}

void QuantumCircuit::show_gate_list() const
{
    for (auto it = gates_targets.begin(); it != gates_targets.end(); it++)
    {
        std::vector<size_t> qubit_eff = it->first;
        QuantumGate gate = it->second;

        std::cout << "{ ";
        for (auto it2 = qubit_eff.begin(); it2 != qubit_eff.end(); it2++)
        {
            std::cout << *it2 << " ";
        }
        std::cout << "} ";

        std::cout << gate.get_type() << std::endl;
    }
}


// end of file
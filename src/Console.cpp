#include "../include/Console.hpp"
#include <limits>
#include <map>

size_t QuantumCircuitConsole::menu_level = 0;

// This map is for convenience in the return value of process_option()
std::map<size_t, std::string> menu_titles =
    {
        {0, "Main"},
        {1, "CircuitOperation"},
        {2, "GateInfo"},
        {3, "VectorOperation"}};

// Banner of the program
void show_title()
{
    std::cout << "════════════════════════════════════════════════════════════════════════════════════" << std::endl;
    std::cout << R"(   ____                        _                        _____  _                    _  _  )" << std::endl;
    std::cout << R"(  / __ \                      | |                      / ____|(_)                  (_)| |)" << std::endl;
    std::cout << R"( | |  | | _   _   __ _  _ __  | |_  _   _  _ __ ___   | |      _  _ __  ___  _   _  _ | |_ )" << std::endl;
    std::cout << R"( | |  | || | | | / _` || '_ \ | __|| | | || '_ ` _ \  | |     | || '__|/ __|| | | || || __|)" << std::endl;
    std::cout << R"( | |__| || |_| || (_| || | | || |_ | |_| || | | | | | | |____ | || |  | (__ | |_| || || |_ )" << std::endl;
    std::cout << R"(  \___\_\ \__,_| \__,_||_| |_| \__| \__,_||_| |_| |_|  \_____||_||_|   \___| \__,_||_| \__|)" << std::endl;
    std::cout << R"(   _____  _                    _         _           )" << std::endl;
    std::cout << R"(  / ____|(_)                  | |       | |      )" << std::endl;
    std::cout << R"( | (___   _  _ __ ___   _   _ | |  __ _ | |_  ___   _ __  )" << std::endl;
    std::cout << R"(  \___ \ | || '_ ` _ \ | | | || | / _` || __|/ _ \ | '__|   )" << std::endl;
    std::cout << R"(  ____) || || | | | | || |_| || || (_| || |_| (_) || |    )" << std::endl;
    std::cout << R"( |_____/ |_||_| |_| |_| \__,_||_| \__,_| \__|\___/ |_|  )" << std::endl;
    std::cout << std::endl;
    std::cout << "════════════════════════════════════════════════════════════════════════════════════" << std::endl;
    std::cout << "  Welcome to QuantumCircuit, a C++ library for simulating quantum circuits. " << std::endl;
    std::cout << "  Author: Zhiyu Liu  2023.5  University of Manchester Third Year Student    " << std::endl;
    std::cout << "════════════════════════════════════════════════════════════════════════════════════" << std::endl;
}

// The main function of the program
void start_program()
{
    // create a map of all the consoles and uses polymorphism to store them
    std::map<std::string, std::unique_ptr<QuantumCircuitConsole>> CONSOLE_MAP;
    CONSOLE_MAP["Main"] = std::make_unique<QauntumCircuitMainConsole>();
    CONSOLE_MAP["CircuitOperation"] = std::make_unique<CircuitOperationConsole>();
    CONSOLE_MAP["GateInfo"] = std::make_unique<DisplayInfoConsole>();
    CONSOLE_MAP["VectorOperation"] = std::make_unique<VectorOperationConsole>();

    show_title();

    std::string current_console = "Main";

    while (true)
    { /*
      display current menu
      --> read_option() --> user input an option (eg. 1) --> return the option (size_t)
      --> process_option() takes the option returned
      --> return the next console
      */
        CONSOLE_MAP[current_console]->display_menu();
        current_console = CONSOLE_MAP[current_console]->process_option(CONSOLE_MAP[current_console]->read_option());
    }
}

void QauntumCircuitMainConsole::display_menu()
{
    std::cout << std::endl;
    std::cout << "╔═════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                 Main Menu                   ║" << std::endl;
    std::cout << "╟─────────────────────────────────────────────╢" << std::endl;
    std::cout << "║ Select an option from the menu below:       ║" << std::endl;
    std::cout << "║---------------------------------------------║" << std::endl;
    std::cout << "║   1. Create a new quantum circuit           ║" << std::endl;
    std::cout << "║---------------------------------------------║" << std::endl;
    std::cout << "║   2. View information about quantum gates   ║" << std::endl;
    std::cout << "║---------------------------------------------║" << std::endl;
    std::cout << "║   3. Perform state vector calculation       ║" << std::endl;
    std::cout << "║---------------------------------------------║" << std::endl;
    std::cout << "║   4. Show information about this project    ║" << std::endl;
    std::cout << "║---------------------------------------------║" << std::endl;
    std::cout << "║   5. Exit the program                       ║" << std::endl;
    std::cout << "╚═════════════════════════════════════════════╝" << std::endl;
}

size_t QauntumCircuitMainConsole::read_option()
{
    std::cout << "Please enter an option between 1 and 5: ";
    size_t option = validate_option(1, 5);
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return option;
}

std::string QauntumCircuitMainConsole::process_option(size_t option)
{
    if (option != 4 && option != 5) // option = 1, 2, 3
        return menu_titles[option];
    else if (option == 4)
    {
        const int width = 80;

        std::cout << "\nThis project aims to simulate the effects of a quantum circuit\n";
        std::cout << "on quantum states, known as qubits.\n\n";

        std::cout << "The interface allows users to visualize a quantum circuit with\n";
        std::cout << "an arbitrary number of qubits and quantum gates.\n\n";

        std::cout << "The project can calculate the evolved final state given\n";
        std::cout << "an initial quantum state.\n\n";

        std::cout << "A vector represents the quantum state, and a matrix represents\n";
        std::cout << "the quantum gate, both of which are imitated by an array.\n\n";

        std::cout << "Several advanced C++ features are used in the project, including\n";
        std::cout << "STL containers, classes with hierarchy, polymorphism,\n";
        std::cout << "move semantics and smart pointers.\n\n";

        pause_and_continue();
        return menu_titles[0];
    }
    else if (option == 5)
    {
        std::cout << "Thank you for using QuantumCircuit. Goodbye!" << std::endl;
        exit(0);
    }
    else
    {
        std::cout << "Invalid option. Please try again." << std::endl;
        return menu_titles[0];
    }
}

void CircuitOperationConsole::display_menu()
{
    // No menu if displayed if the user enters this console the first time.
    if (QuantumCircuitConsole::menu_level == 1)
    {
        std::cout << std::endl;
        std::cout << "╔════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║           Circuit Operation Menu               ║" << std::endl;
        std::cout << "╟────────────────────────────────────────────────╢" << std::endl;
        std::cout << "║ Select an option from the menu below:          ║" << std::endl;
        std::cout << "║------------------------------------------------║" << std::endl;
        std::cout << "║   1. Add a Hadamard Gate                       ║" << std::endl;
        std::cout << "║------------------------------------------------║" << std::endl;
        std::cout << "║   2. Add a Swap Gate                           ║" << std::endl;
        std::cout << "║------------------------------------------------║" << std::endl;
        std::cout << "║   3. Add a CNOT Gate                           ║" << std::endl;
        std::cout << "║------------------------------------------------║" << std::endl;
        std::cout << "║   4. Add a Pauli Gate                          ║" << std::endl;
        std::cout << "║------------------------------------------------║" << std::endl;
        std::cout << "║   5. Add a Phase Gate                          ║" << std::endl;
        std::cout << "║------------------------------------------------║" << std::endl;
        std::cout << "║   6. Show the current circuit                  ║" << std::endl;
        std::cout << "╠════════════════════════════════════════════════╣" << std::endl;
        std::cout << "║   7. Simulate the circuit with a given state   ║" << std::endl;
        std::cout << "║------------------------------------------------║" << std::endl;
        std::cout << "║   8. Create another circuit                    ║" << std::endl;
        std::cout << "║------------------------------------------------║" << std::endl;
        std::cout << "║   9. Return to main menu                       ║" << std::endl;
        std::cout << "║------------------------------------------------║" << std::endl;
        std::cout << "║  10. Exit the program                          ║" << std::endl;
        std::cout << "╚════════════════════════════════════════════════╝" << std::endl;
        std::cout << std::endl;
    }
    else if (QuantumCircuitConsole::menu_level == 2)
    {
        std::cout << std::endl;
        std::cout << "╔═════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║        State Vector Calculation Menu            ║" << std::endl;
        std::cout << "╟─────────────────────────────────────────────────╢" << std::endl;
        std::cout << "║ What kind of state would you like to simulate?  ║" << std::endl;
        std::cout << "║-------------------------------------------------║" << std::endl;
        std::cout << "║   1. A standard basis state.                    ║" << std::endl;
        std::cout << "║-------------------------------------------------║" << std::endl;
        std::cout << "║   2. A Bell basis state.                        ║" << std::endl;
        std::cout << "║-------------------------------------------------║" << std::endl;
        std::cout << "║   3. The GHZ entangled state.                   ║" << std::endl;
        std::cout << "║-------------------------------------------------║" << std::endl;
        std::cout << "║   4. The W entangled state.                     ║" << std::endl;
        std::cout << "╚═════════════════════════════════════════════════╝" << std::endl;
    }
    else
    {
        ; // Do nothing.
    }
}

size_t CircuitOperationConsole::read_option()
{
    if (QuantumCircuitConsole::menu_level == 0)
    {
        // For creating a new circuit.
        std::cout << "Please enter the number of qubits: ";
        size_t option = validate_option(1, 100);
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return option;
    }
    else if (QuantumCircuitConsole::menu_level == 1)
    {
        std::cout << "Please enter an option between 1 and 10: ";
        size_t gate_option = validate_option(1, 10);
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return gate_option;
    }
    else
    {
        std::cout << "You choice: ";
        size_t state_option = validate_option(1, 4);
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return state_option;
    }
}

std::string CircuitOperationConsole::process_option(size_t option)
{
    if (QuantumCircuitConsole::menu_level == 0)
    {
        qubit_n = option;
        circuit = QuantumCircuit{qubit_n};
        std::cout << "\nA new quantum circuit with " << qubit_n << " qubits has been created.\n";

        QuantumCircuitConsole::menu_level = 1;
        return menu_titles[1];
    }
    if (QuantumCircuitConsole::menu_level == 1)
    {
        switch (option)
        {
        // Switch cases for the circuit menu
        case 1:
        {
            // Add a Hadamard Gate
            std::cout << "To which qubit would you like to add a Hadamard Gate? Enter: ";
            size_t qubit_eff = validate_option(0, qubit_n - 1);
            circuit.add_Hadamard(qubit_eff);

            pause_and_continue();
            return menu_titles[1];
        }
        case 2:
        {
            // Add a Swap Gate
            if (qubit_n == 1)
            {
                std::cout << "There is only one qubit in the circuit. You cannot add a Swap Gate." << std::endl;
                pause_and_continue();
                return menu_titles[1];
            }

            std::cout << "Which two qubits would you like to add a Swap Gate? Enter(e.g.: 1, 2): ";
            char comma;
            size_t qubit1, qubit2;

            std::string input;
            while (true)
            {
                std::getline(std::cin, input);
                std::stringstream ss(input);

                if (ss >> qubit1 >> comma >> qubit2 && comma == ',' && qubit1 < qubit_n && qubit2 < qubit_n && qubit1 != qubit2)
                    break;
                else
                {
                    std::cout << "Invalid input. Please enter two qubit indices between 0 and " << qubit_n - 1;
                    std::cout << " and separate them with a comma: ";
                }
            }

            circuit.add_Swap(qubit1, qubit2);

            pause_and_continue();
            return menu_titles[1];
        }
        case 3:
        {
            if (qubit_n == 1)
            {
                std::cout << "There is only one qubit in the circuit. You cannot add a CNOT Gate." << std::endl;
                pause_and_continue();
                return menu_titles[1];
            }
            // Add a CNOT Gate
            size_t control_qubit;
            size_t target_qubit;

            while (true)
            {
                std::cout << "Which qubit would you like to add a control qubit to? Enter: ";
                control_qubit = validate_option(0, qubit_n - 1);
                std::cout << "Which qubit would you like to add a target qubit to? Enter: ";
                target_qubit = validate_option(0, qubit_n - 1);

                if (control_qubit == target_qubit)
                    std::cout << "The control qubit and the target qubit cannot be the same. Please try again.\n";
                else
                    break; // valid inputs, exit the loop
            }

            circuit.add_CNOT(control_qubit, target_qubit);

            pause_and_continue();
            return menu_titles[1];
        }
        case 4:
        {
            // Add a Pauli Gate
            std::cout << "Which qubit would you like to add a Pauli Gate to? Enter: ";
            size_t qubit_eff = validate_option(0, qubit_n - 1);
            std::cout << "Which Pauli Gate would you like to add?\n";
            std::cout << " 1. Pauli X\n";
            std::cout << " 2. Pauli Y\n";
            std::cout << " 3. Pauli Z\n";
            std::cout << "Enter: ";
            size_t pauli_option = validate_option(1, 3);

            switch (pauli_option)
            {
            case 1:
                circuit.add_Pauli(qubit_eff, "X");
                break;
            case 2:
                circuit.add_Pauli(qubit_eff, "Y");
                break;
            case 3:
                circuit.add_Pauli(qubit_eff, "Z");
                break;
            default:
                std::cout << "Invalid option.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }

            pause_and_continue();
            return menu_titles[1];
        }
        case 5:
        {
            // Add a Phase Gate
            std::cout << "Which qubit would you like to add a Phase Gate to? Enter: ";
            size_t qubit_eff = validate_option(0, qubit_n - 1);
            std::cout << "Enter the phase angle: (0 - 360) ";
            double phase_angle = read_angle_to_radian();
            circuit.add_Phase(qubit_eff, phase_angle);

            pause_and_continue();
            return menu_titles[1];
        }
        case 6:
        {
            circuit.display_circuit();
            pause_and_continue();
            return menu_titles[1];
        }
        case 7:
        {
            // Simulate an initial state evolving through the circuit
            // The options are at menu level 2
            QuantumCircuitConsole::menu_level = 2;
            pause_and_continue();
            return menu_titles[1];
        }
        case 8:
        {
            // Create a new circuit
            QuantumCircuitConsole::menu_level = 0;
            return menu_titles[1];
        }
        case 9:
        {
            // Return to the main menu
            QuantumCircuitConsole::menu_level = 0;
            return menu_titles[0];
        }
        case 10:
        {
            exit(0);
        }
        }
    }
    if (QuantumCircuitConsole::menu_level == 2)
    {
        size_t state_option = option;
        Statevector initial_state;
        Statevector final_state;
        initial_state = get_initial_state(state_option);
        final_state = evolve(initial_state, circuit, "");

        std::cout << "The initial state is: \n";
        initial_state.display_column();
        std::cout << "The final state is: \n";
        final_state.display_column();

        QuantumCircuitConsole::menu_level = 1;
        pause_and_continue();
        return menu_titles[1];
    }
    return menu_titles[0];
}

// Get the initial state for option 7.
Statevector CircuitOperationConsole::get_initial_state(size_t option)
{
    Statevector initial_state(qubit_n);

    if (option == 1)
    {
        std::cout << "\nPlease enter the state (eg: 01, 110): ";
        std::string state_str;
        std::cin >> state_str;

        if (state_str.length() != qubit_n)
        {
            std::cout << "The length of the state must be equal to the number of qubits.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return get_initial_state(option);
        }
        else
        {
            // Check if the string only contains '0' or '1'
            for (char &c : state_str)
            {
                if (c != '0' && c != '1')
                {
                    std::cout << "The state can only contain binary digits (0 or 1).\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    return get_initial_state(option);
                }
            }
            initial_state = generate_state(qubit_n, "std", state_str);
        }
    }
    else if (option == 2)
    {
        if (qubit_n != 2)
        {
            std::cout << "The Bell basis state is only available for 2 qubits.\n";
            return initial_state;
        }
        else
        {
            std::cout << "Please enter the Bell basis (eg: 00, 01): ";
            std::string bell_basis;
            std::cin >> bell_basis;

            // Check if the string length is exactly 2 and contains only '0' or '1'

            if (bell_basis.length() != 2 || (bell_basis[0] != '0' && bell_basis[0] != '1') || (bell_basis[1] != '0' && bell_basis[1] != '1'))
            {
                std::cout << "The Bell basis state must be a binary pair (00, 01, 10, or 11).\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return get_initial_state(option);
            }
            initial_state = generate_state(qubit_n, "Bell", bell_basis);
        }
    }
    else if (option == 3)
    {
        if (qubit_n != 3)
        {
            std::cout << "The GHZ entangled state is only available for 3 qubits.\n";
            return initial_state;
        }
        else
            initial_state = generate_state(qubit_n, "GHZ");
    }
    else if (option == 4)
    {
        if (qubit_n != 3)
        {
            std::cout << "The W entangled state is only available for 3 qubits.\n";
            return initial_state;
        }
        else
            initial_state = generate_state(qubit_n, "W");
    }
    else
    {
        std::cout << "Invalid option.\n";
        return initial_state;
    }
    pause_and_continue();
    return initial_state;
}

void DisplayInfoConsole::display_menu()
{
    std::cout << std::endl;
    std::cout << "╔═══════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║    Quantum Gates available in this library:           ║" << std::endl;
    std::cout << "╟───────────────────────────────────────────────────────╢" << std::endl;
    std::cout << "║   1. Hadamard Gate                                    ║" << std::endl;
    std::cout << "║-------------------------------------------------------║" << std::endl;
    std::cout << "║   2. Swap Gate                                        ║" << std::endl;
    std::cout << "║-------------------------------------------------------║" << std::endl;
    std::cout << "║   3. CNOT Gate                                        ║" << std::endl;
    std::cout << "║-------------------------------------------------------║" << std::endl;
    std::cout << "║   4. Pauli Gates                                      ║" << std::endl;
    std::cout << "║-------------------------------------------------------║" << std::endl;
    std::cout << "║   5. Phase Gate                                       ║" << std::endl;
    std::cout << "║-------------------------------------------------------║" << std::endl;
    std::cout << "║   6. Identity Gate                                    ║" << std::endl;
    std::cout << "║-------------------------------------------------------║" << std::endl;
    std::cout << "║   7. Return to main menu                              ║" << std::endl;
    std::cout << "║-------------------------------------------------------║" << std::endl;
    std::cout << "║   8. Exit the program                                 ║" << std::endl;
    std::cout << "╚═══════════════════════════════════════════════════════╝" << std::endl;
    std::cout << std::endl;
}

size_t DisplayInfoConsole::read_option()
{
    std::cout << "Please enter an option between 1 and 8: ";
    size_t option = validate_option(1, 8);
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return option;
}

std::string DisplayInfoConsole::process_option(size_t option)
{
    switch (option)
    {
    case 1:
    {
        std::cout << "\nA 2x2 Hadamard Gate: " << std::endl;
        QuantumGate::Hadamard2x2.display_matrix();
        std::cout << "\nTwo 2x2 Hadamard Gates processing the same qubit: " << std::endl;
        QuantumGate HH = QuantumGate::Hadamard2x2 * QuantumGate::Hadamard2x2;
        HH.display_matrix();
        std::cout << "The Hadamard being unitary and Hermitian => HH=I.\n"
                  << std::endl;
        break;
    }
    case 2:
    {
        std::cout << "\nA 4x4 Swap Gate: " << std::endl;
        QuantumGate::SWAP4x4.display_matrix();
        std::cout << std::endl;
        break;
    }
    case 3:
    {
        std::cout << "\nA 4x4 CNOT Gate: " << std::endl;
        QuantumGate::CNOT4x4.display_matrix();
        std::cout << std::endl;
        break;
    }
    case 4:
    {
        std::cout << "\nA 2x2 Pauli X Gate: " << std::endl;
        QuantumGate::PauliX.display_matrix();
        std::cout << "\nA 2x2 Pauli Y Gate: " << std::endl;
        QuantumGate::PauliY.display_matrix();
        std::cout << "\nA 2x2 Pauli Z Gate: " << std::endl;
        QuantumGate::PauliZ.display_matrix();
        std::cout << std::endl;
        break;
    }
    case 5:
    {
        std::cout << "\nA 2x2 Phase Gate: " << std::endl;
        std::cout << "┌ 1 0          ┐" << std::endl;
        std::cout << "└ 0 e^{i\\theta}┘" << std::endl;
        std::cout << std::endl;
        break;
    }
    case 6:
    {
        std::cout << "\nA 2x2 Identity Gate: " << std::endl;
        QuantumGate::Identity2x2.display_matrix();
        std::cout << std::endl;
        break;
    }
    case 7:
    {
        return menu_titles[0];
    }
    case 8:
    {
        exit(0);
    }
    }
    pause_and_continue();
    return menu_titles[2];
}

void VectorOperationConsole::display_menu()
{
    std::cout << std::endl;
    std::cout << "╔═════════════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║        Vector Operations available in this library                  ║" << std::endl;
    std::cout << "╟─────────────────────────────────────────────────────────────────────╢" << std::endl;
    std::cout << "║ Select an option from the menu below:                               ║" << std::endl;
    std::cout << "║---------------------------------------------------------------------║" << std::endl;
    std::cout << "║   1. Create a set of standard basis                                 ║" << std::endl;
    std::cout << "║---------------------------------------------------------------------║" << std::endl;
    std::cout << "║   2. Create a set of Bell basis                                     ║" << std::endl;
    std::cout << "║---------------------------------------------------------------------║" << std::endl;
    std::cout << "║   3. Return to the main menu                                        ║" << std::endl;
    std::cout << "╚═════════════════════════════════════════════════════════════════════╝" << std::endl;
}

size_t VectorOperationConsole::read_option()
{
    std::cout << "Please enter an option between 1 and 4: ";
    size_t option = validate_option(1, 3);
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return option;
}

std::string VectorOperationConsole::process_option(size_t option)
{
    if (option == 1)
    {
        std::map<std::string, Statevector> basis_2 = generate_std_basis(2);
        std::map<std::string, Statevector> basis_4 = generate_std_basis(3);
        std::map<std::string, Statevector> basis_8 = generate_std_basis(4);

        std::cout << "\nStandard basis for 2 qubits: " << std::endl;
        for (auto it = basis_2.begin(); it != basis_2.end(); ++it)
        {
            std::cout << "|" << it->first << "> : ";
            it->second.display_row();
        }
        std::cout << std::endl;
        pause_and_continue();

        std::cout << "\nStandard basis for 3 qubits: " << std::endl;
        for (auto it = basis_4.begin(); it != basis_4.end(); ++it)
        {
            std::cout << "|" << it->first << "> : ";
            it->second.display_row();
        }
        std::cout << std::endl;
        pause_and_continue();

        std::cout << "\nStandard basis for 4 qubits: " << std::endl;
        for (auto it = basis_8.begin(); it != basis_8.end(); ++it)
        {
            std::cout << "|" << it->first << "> : ";
            it->second.display_row();
        }
        std::cout << std::endl;

        pause_and_continue();
        return menu_titles[3];
    }
    else if (option == 2)
    {
        std::map<std::string, Statevector> basis_2 = generate_std_basis(2);
        Statevector std_00 = basis_2["00"];
        Statevector std_01 = basis_2["01"];
        Statevector std_10 = basis_2["10"];
        Statevector std_11 = basis_2["11"];

        Statevector Bell_00 = (std_00 + std_11) / std::sqrt(2);
        Statevector Bell_01 = (std_01 + std_10) / std::sqrt(2);
        Statevector Bell_10 = (std_00 - std_11) / std::sqrt(2);
        Statevector Bell_11 = (std_01 - std_10) / std::sqrt(2);

        std::cout << "\nBell basis for 2 qubits: " << std::endl;
        std::cout << "|00_B> : ";
        Bell_00.display_row();
        std::cout << "|01_B> : ";
        Bell_01.display_row();
        std::cout << "|10_B> : ";
        Bell_10.display_row();
        std::cout << "|11_B> : ";
        Bell_11.display_row();

        pause_and_continue();
        return menu_titles[3];
    }
    else
    {
        return menu_titles[0];
    }
}

// end of file
#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include "QuantumCircuit.hpp"
#include "Format.hpp"

/*
Description: Header file containing the declaration of classes related to a quantum circuit console application.
This file defines the abstract base class QuantumCircuitConsole and its derived classes.
Each derived class represents a specific console functionality related to quantum circuit operations.
The classes provide methods for displaying menus, reading user input, and processing options.
The start_program() function serves as the entry point for the quantum circuit console application.
*/

class QuantumCircuitConsole
{
public:
    virtual void display_menu() = 0;
    virtual size_t read_option() = 0;
    virtual std::string process_option(size_t option) = 0;
    virtual ~QuantumCircuitConsole() {} 
    // menu_level is used to control submenus 
    static size_t menu_level;
};
 
class QauntumCircuitMainConsole : public QuantumCircuitConsole
{
public:
    void display_menu();
    size_t read_option();
    std::string process_option(size_t option);
};

class CircuitOperationConsole : public QuantumCircuitConsole
{
private:
    size_t qubit_n = 0;
    QuantumCircuit circuit;
public:
    void display_menu();
    size_t read_option();
    std::string process_option(size_t option);
    Statevector get_initial_state(size_t option);
};

class DisplayInfoConsole : public QuantumCircuitConsole
{
public:
    void display_menu();
    size_t read_option();
    std::string process_option(size_t option);
};

class VectorOperationConsole : public QuantumCircuitConsole
{
public:
    void display_menu();
    size_t read_option();
    std::string process_option(size_t option);
};

void start_program();

#endif
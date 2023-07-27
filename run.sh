mkdir -p obj

g++ -std=c++14 -c -o obj/main.o main.cpp
g++ -std=c++14 -c -o obj/Format.o src/Format.cpp
g++ -std=c++14 -c -o obj/Console.o src/Console.cpp
g++ -std=c++14 -c -o obj/QuantumCircuit.o src/QuantumCircuit.cpp
g++ -std=c++14 -c -o obj/QuantumGate.o src/QuantumGate.cpp
g++ -std=c++14 -c -o obj/Statevector.o src/Statevector.cpp
g++ -std=c++14 -c -o obj/CNOT.o src/QuantumGates/CNOT.cpp
g++ -std=c++14 -c -o obj/Hadamard.o src/QuantumGates/Hadamard.cpp
g++ -std=c++14 -c -o obj/Pauli.o src/QuantumGates/Pauli.cpp
g++ -std=c++14 -c -o obj/Phase.o src/QuantumGates/Phase.cpp
g++ -std=c++14 -c -o obj/Swap.o src/QuantumGates/Swap.cpp

g++ -o bin/main \
obj/main.o \
obj/Format.o \
obj/Console.o \
obj/QuantumCircuit.o \
obj/QuantumGate.o \
obj/Statevector.o \
obj/CNOT.o \
obj/Hadamard.o \
obj/Pauli.o \
obj/Phase.o \
obj/Swap.o

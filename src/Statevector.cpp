#include "../include/Statevector.hpp"

Statevector::Statevector()
{
    qubit_n = 0;
    array = std::make_unique<std::complex<double>[]>(1);
    array[0] = 0;
}

// Constructor for 0 statevector with n qubits
Statevector::Statevector(size_t qubit_n_) : qubit_n(qubit_n_)
{
    size_t array_size = pow(2, qubit_n);
    array = std::make_unique<std::complex<double>[]>(array_size);

    for (int i = 0; i < pow(2, qubit_n); i++)
    {
        array[i] = 0;
    }
}

// Parameterized constructor that takes a list of qubit states in ket notation
Statevector::Statevector(std::initializer_list<int> qubit_states)
{
    qubit_n = qubit_states.size();
    size_t array_size = pow(2, qubit_n);

    array = std::make_unique<std::complex<double>[]>(array_size);
    std::vector<int> qubit_list(qubit_states);

    int pos = 0;
    for (int i = 0; i < qubit_n; i++)
    {
        pos += qubit_list[i] * pow(2, qubit_n - i - 1);
    }

    for (int i = 0; i < pow(2, qubit_n); i++)
    {
        if (i == pos)
            array[i] = 1;
        else
            array[i] = 0;
    }
}

// Parameterized constructor that takes a list of complex numbers
Statevector::Statevector(std::initializer_list<std::complex<double>> elements)
{
    // Calculate the number of qubits.
    double log2size = std::log2(elements.size());

    // Check if the number of elements is a power of 2.
    if (log2size != std::floor(log2size))
    {
        throw std::invalid_argument("The number of elements must be a power of 2.");
    }

    qubit_n = static_cast<int>(log2size);
    size_t array_size = pow(2, qubit_n);

    array = std::make_unique<std::complex<double>[]>(array_size);
    std::vector<std::complex<double>> element_list(elements);

    for (int i = 0; i < array_size; i++)
    {
        array[i] = element_list[i];
    }
}

// Copy constructor
Statevector::Statevector(const Statevector &s)
{
    qubit_n = s.qubit_n;
    size_t array_size = pow(2, qubit_n);

    array = std::make_unique<std::complex<double>[]>(array_size);
    for (int i = 0; i < pow(2, qubit_n); i++)
    {
        array[i] = s.array[i];
    }
    this->round();
}

// Copy assignment operator
Statevector &Statevector::operator=(const Statevector &s)
{
    if (this == &s)
        return *this;

    qubit_n = s.qubit_n;
    size_t array_size = pow(2, qubit_n);

    array = std::make_unique<std::complex<double>[]>(array_size);
    for (int i = 0; i < pow(2, qubit_n); i++)
    {
        array[i] = s.array[i];
    }

    this->round();
    return *this;
}

// Move constructor
Statevector::Statevector(Statevector &&s)
{
    qubit_n = s.qubit_n;
    array = std::move(s.array);

    s.qubit_n = 0;
    s.array = std::make_unique<std::complex<double>[]>(1);
    s.array[0] = 0;

    this->round();
}

// Move assignment operator
Statevector &Statevector::operator=(Statevector &&s)
{
    if (this == &s)
        return *this;

    qubit_n = s.qubit_n;
    array = std::move(s.array);

    s.qubit_n = 0;
    s.array = std::make_unique<std::complex<double>[]>(1);
    s.array[0] = 0;

    this->round();
    return *this;
}

// Overload + operator
Statevector Statevector::operator+(const Statevector &s)
{
    Statevector result(s);
    for (int i = 0; i < pow(2, qubit_n); i++)
    {
        result.array[i] += array[i];
    }
    return result;
}

Statevector Statevector::operator-(const Statevector &s)
{
    Statevector result(s);
    for (int i = 0; i < pow(2, qubit_n); i++)
    {
        result.array[i] -= array[i];
    }
    return result;
}

Statevector Statevector::operator/(const std::complex<double> &c)
{
    Statevector result(*this);
    for (int i = 0; i < pow(2, qubit_n); i++)
    {
        result.array[i] /= c;
    }
    return result;
}

// Overloading [] operator
std::complex<double> &Statevector::operator[](size_t i)
{
    if (i >= pow(2, qubit_n))
    {
        std::cout << "Error: trying to access an element out of bounds" << std::endl;
        throw("index out of bounds");
    }
    return array[i];
}

// Overloading [] operator for const objects
const std::complex<double> &Statevector::operator[](size_t i) const
{
    if (i >= pow(2, qubit_n))
    {
        std::cout << "Error: trying to access an element out of bounds" << std::endl;
        throw("index out of bounds");
    }
    return array[i];
}

// Displaying the statevector in row form
void Statevector::display_row()
{
    std::cout << "[";
    for (int i = 0; i < pow(2, qubit_n); i++)
    {
        std::cout << " " << complex_to_str(array[i]) << " ";
    }
    std::cout << "]" << std::endl;
}

// Auxiliary function to get the maximum width of a complex number in the statevector
size_t Statevector::get_max_width() const
{
    size_t max_width = 0;
    for (int i = 0; i < pow(2, qubit_n); i++)
    {
        size_t width = complex_to_str(array[i]).length();
        max_width = std::max(max_width, width);
    }
    return max_width;
}

// Displaying the statevector in column form
void Statevector::display_column() 
{
    size_t width = get_max_width();

    for (int i = 0; i < pow(2, qubit_n); i++)
    {
        if (i == 0)
        {
            std::cout << "┌ ";
            std::cout << std::setw(width) << std::right << complex_to_str(array[i]);
            std::cout << " ┐" << std::endl;
        }
        else if (i == pow(2, qubit_n) - 1)
        {
            std::cout << "└ ";
            std::cout << std::setw(width) << std::right << complex_to_str(array[i]);
            std::cout << " ┘" << std::endl;
        }
        else
        {
            std::cout << "| ";
            std::cout << std::setw(width) << std::right << complex_to_str(array[i]);
            std::cout << " |" << std::endl;
        }
    }
}

// Generate standard basis
std::map<std::string, Statevector> generate_std_basis(size_t qubit_n)
{
    std::map<std::string, Statevector> basis;
    for (int i = 0; i < pow(2, qubit_n); i++)
    {
        Statevector s(qubit_n);
        s[i] = 1;
        std::string ket_representation = "";
        for (int j = qubit_n - 1; j >= 0; j--)
        {
            ket_representation += (i & (1 << j)) ? "1" : "0";
        }

        basis[ket_representation] = s;
    }
    return basis;
}

// Generate state
Statevector generate_state(size_t qubit_n, std::string state_kind, std::string state_str)
{
    Statevector s(qubit_n);
    if (state_kind == "std")
    {
        // state_str = 000110, 110 ...
        s = generate_std_basis(qubit_n)[state_str];
    }
    else if (state_kind == "Bell")
    {
        if (state_str == "00")
        {
            s = (generate_std_basis(2)["00"] + generate_std_basis(2)["11"]) / sqrt(2);
        }
        else if (state_str == "01")
        {
            s = (generate_std_basis(2)["00"] - generate_std_basis(2)["11"]) / sqrt(2);
        }
        else if (state_str == "10")
        {
            s = (generate_std_basis(2)["01"] + generate_std_basis(2)["10"]) / sqrt(2);
        }
        else if (state_str == "11")
        {
            s = (generate_std_basis(2)["01"] - generate_std_basis(2)["10"]) / sqrt(2);
        }
        else
        {
            std::cout << "Error: invalid Bell state" << std::endl;
            throw("invalid Bell state");
        }
    }
    else if (state_kind == "GHZ")
    {
        s = generate_std_basis(3)["000"] + generate_std_basis(3)["111"];
    }
    else if (state_kind == "W")
    {
        // Custom W state
        s = generate_std_basis(3)["001"] + generate_std_basis(3)["010"] + generate_std_basis(3)["100"];
    }
    else if (state_kind == "random")
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0, 1);
        for (int i = 0; i < pow(2, qubit_n); i++)
        {
            double real = dis(gen);
            double imag = dis(gen);
            s[i] = std::complex<double>(real, imag);
        }
    }
    else if (state_kind == "custom")
    {
        ;
    }
    else
    {
        s = generate_std_basis(qubit_n)["0"];
    }
    return s;
}

// Round the statevector to 0 if the absolute value is less than 1e-10
void Statevector::round()
{
    for (int i = 0; i < pow(2, qubit_n); i++)
    {
        if (std::abs(array[i].real()) < 1e-10)
            array[i].real(0);
        if (std::abs(array[i].imag()) < 1e-10)
            array[i].imag(0);
    }
}

void display_std_basis(size_t qubit_n)
{
    std::map<std::string, Statevector> basis = generate_std_basis(qubit_n);
    for (auto &i : basis)
    {
        std::cout << "|" << i.first << "> : ";
        i.second.display_row();
    }
}
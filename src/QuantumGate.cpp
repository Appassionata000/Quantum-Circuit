#include "../include/QuantumGate.hpp"

QuantumGate::QuantumGate()
{
    rows = 0;
    cols = 0;
    type = Type::Custom;
    array = nullptr;
}

QuantumGate::QuantumGate(size_t size) : 
rows(size), cols(size), type(Type::Custom)
{
    array = std::make_unique<std::complex<double>[]>(size * size);

    for (size_t i = 0; i < size * size; i++)
    {
        array[i] = 0;
    }
}

// Parameterized constructor
QuantumGate::QuantumGate(Type type_, const size_t size_, std::initializer_list<std::complex<double>> elements) :
rows(size_), cols(size_), type(type_)
{
    array = std::make_unique<std::complex<double>[]>(size_ * size_);

    for (size_t i = 0; i < size_ * size_; i++)
    {
        array[i] = *(elements.begin() + i);
    }

    this->round();
}

// Copy constructor
QuantumGate::QuantumGate(const QuantumGate &q) :
rows(q.rows), cols(q.cols), type(q.type)
{
    array = std::make_unique<std::complex<double>[]>(rows * cols);

    for (size_t i = 0; i < rows * cols; i++)
    {
        array[i] = q.array[i];
    }

    this->round();
}

// Copy assignment operator
QuantumGate &QuantumGate::operator=(const QuantumGate &q)
{
    if (this != &q)
    {
        rows = q.rows;
        cols = q.cols;
        type = q.type;
        array = std::make_unique<std::complex<double>[]>(rows * cols);

        for (size_t i = 0; i < rows * cols; i++)
        {
            array[i] = q.array[i];
        }
    }

    this->round();
    return *this;
}

// Move constructor
QuantumGate::QuantumGate(QuantumGate &&q) :
rows(std::move(q.rows)), cols(std::move(q.cols)), type(std::move(q.type)), array(std::move(q.array))
{}

// Move assignment operator
QuantumGate &QuantumGate::operator=(QuantumGate &&q)
{
    if (this != &q)
    {
        rows = std::move(q.rows);
        cols = std::move(q.cols);
        type = std::move(q.type);
        array = std::move(q.array);
    }

    this->round();
    return *this;
}

// Overload () operator
std::complex<double> &QuantumGate::operator()(size_t row, size_t col)
{
    return array[(row - 1) * cols + col - 1];
}

// Overload () operator for const objects
const std::complex<double> &QuantumGate::operator()(size_t row, size_t col) const
{
    return array[(row - 1) * cols + col - 1];
}

// Overload operators
QuantumGate QuantumGate::operator+(const QuantumGate &q) const
{
    if (this->size() != q.size())
    {
        std::cout << "Error: trying to add matrices with incompatible dimensions" << std::endl;
        throw("incompatible dimensions");
    }

    QuantumGate result(this->rows);

    for (size_t i = 1; i <= result.rows; i++)
    {
        for (size_t j = 1; j <= result.cols; j++)
        {
            result(i, j) = (*this)(i, j) + q(i, j);
        }
    }

    return result;
}

QuantumGate QuantumGate::operator-(const QuantumGate &q) const
{
    // Check if the matrices have the same dimensions
    if (this->rows != q.rows || this->cols != q.cols)
        throw std::invalid_argument("QuantumGate dimensions must match for subtraction!");

    QuantumGate result(this->rows);

    for (size_t i = 0; i < result.rows; i++)
    {
        for (size_t j = 0; j < result.cols; j++)
        {
            result(i, j) = (*this)(i, j) - q(i, j);
        }
    }

    return result;
}

QuantumGate QuantumGate::operator*(const QuantumGate &q) const
{
    if (this->size() != q.size())
    {
        std::cout << "Error: trying to multiply matrices with incompatible dimensions" << std::endl;
        throw("incompatible dimensions");
    }

    QuantumGate result(this->rows);

    for (size_t i = 1; i <= result.rows; i++)
    {
        for (size_t j = 1; j <= result.cols; j++)
        {
            std::complex<double> sum{0.0, 0.0};
            for (size_t k = 1; k <= this->cols; k++)
            {
                sum += (*this)(i, k) * q(k, j);
            }
            result(i, j) = sum;
        }
    }

    return result;
}

QuantumGate QuantumGate::operator*(const std::complex<double> &c) const
{
    QuantumGate result(this->rows);

    for (size_t i = 1; i <= result.rows; i++)
    {
        for (size_t j = 1; j <= result.cols; j++)
        {
            result(i, j) = (*this)(i, j) * c;
        }
    }

    return result;
}

QuantumGate QuantumGate::kronecker(const QuantumGate &q) const
{
    QuantumGate result(this->rows * q.rows);

    for (size_t i = 1; i <= this->rows; i++)
    {
        for (size_t j = 1; j <= this->cols; j++)
        {
            for (size_t k = 1; k <= q.rows; k++)
            {
                for (size_t l = 1; l <= q.cols; l++)
                {
                    result((i - 1) * q.rows + k, (j - 1) * q.cols + l) = (*this)(i, j) * q(k, l);
                }
            }
        }
    }

    return result;
}

QuantumGate QuantumGate::operator+(QuantumGate &&q) const
{
    if (this->size() != q.size())
    {
        std::cout << "Error: trying to add matrices with incompatible dimensions" << std::endl;
        throw("incompatible dimensions");
    }

    QuantumGate result(this->rows);

    for (size_t i = 1; i <= result.rows; i++)
    {
        for (size_t j = 1; j <= result.cols; j++)
        {
            result(i, j) = (*this)(i, j) + q(i, j);
        }
    }

    return result;
}

QuantumGate QuantumGate::operator-(QuantumGate &&q) const
{
    // Ensuring the matrices have the same dimensions
    if (this->rows != q.rows || this->cols != q.cols)
        throw std::invalid_argument("QuantumGate dimensions must match for subtraction!");

    QuantumGate result(this->rows);

    for (size_t i = 0; i < result.rows; i++)
    {
        for (size_t j = 0; j < result.cols; j++)
        {
            result(i, j) = (*this)(i, j) - q(i, j);
        }
    }

    return result;
}

QuantumGate QuantumGate::operator*(QuantumGate &&q) const
{
    if (this->size() != q.size())
    {
        std::cout << "Error: trying to multiply matrices with incompatible dimensions" << std::endl;
        throw("incompatible dimensions");
    }

    QuantumGate result(this->rows);

    for (size_t i = 1; i <= result.rows; i++)
    {
        for (size_t j = 1; j <= result.cols; j++)
        {
            std::complex<double> sum{0.0, 0.0};
            for (size_t k = 1; k <= this->cols; k++)
            {
                sum += (*this)(i, k) * q(k, j);
            }
            result(i, j) = sum;
        }
    }

    return result;
}

QuantumGate& QuantumGate::operator+=(const QuantumGate &q)
{
    if (this->size() != q.size())
    {
        std::cout << "Error: trying to add matrices with incompatible dimensions" << std::endl;
        throw("incompatible dimensions");
    }

    for (size_t i = 1; i <= this->rows; i++)
    {
        for (size_t j = 1; j <= this->cols; j++)
        {
            (*this)(i, j) += q(i, j);
        }
    }

    return *this;
}

QuantumGate& QuantumGate::operator-=(const QuantumGate &q)
{
    if (this->size() != q.size())
    {
        std::cout << "Error: trying to subtract matrices with incompatible dimensions" << std::endl;
        throw("incompatible dimensions");
    }

    for (size_t i = 1; i <= this->rows; i++)
    {
        for (size_t j = 1; j <= this->cols; j++)
        {
            (*this)(i, j) -= q(i, j);
        }
    }

    return *this;
}

// Format the matrix as a string
std::vector<std::string> QuantumGate::to_string()
{
    std::vector<std::string> matrix_strings;

    for (int i = 0; i < rows * cols; i++)
    {
        std::string str = complex_to_str(array[i]);
        matrix_strings.push_back(str);
    }

    return matrix_strings;
}

std::vector<size_t> QuantumGate::get_max_width()
{
    std::vector<std::string> str = this->to_string();
    std::vector<size_t> max_widths;

    for (int col_n = 0; col_n < cols; col_n++)
    {
        size_t max_width = 0;

        for (int row_n = 0; row_n < rows; row_n++)
        {
            size_t width = str[row_n * cols + col_n].length();
            max_width = std::max(max_width, width);
        }

        max_widths.push_back(max_width);
    }

    return max_widths;
}

void QuantumGate::display_matrix()
{
    int i = 1, j = 1;
    std::vector<std::string> matrix_str = this->to_string();
    std::vector<size_t> width = this->get_max_width();

    for (i = 1; i <= rows; ++i, j = 1)
    {
        if (i == 1 && j == 1)
            std::cout << "┌ ";

        else if (i == rows && j == 1)
            std::cout << "└ ";

        else
            std::cout << "| ";

        for (j = 1; j <= cols; ++j)
            std::cout << std::setw(width[j - 1]) << std::right << matrix_str[(i - 1) * cols + (j - 1)] << " ";

        if (i == 1 && j == cols + 1)
            std::cout << "┐" << std::endl;

        else if (i == rows && j == cols + 1)
            std::cout << "┘" << std::endl;

        else
            std::cout << "|" << std::endl;
    }
}

void QuantumGate::round()
{
    for (int i = 0; i < rows * cols; i ++)
    {
        if (std::abs(array[i].real()) < ROUND_MINIMUM)
        {
            array[i] = std::complex<double>(0, array[i].imag());
        }
        if (std::abs(array[i].imag()) < ROUND_MINIMUM)
        {
            array[i] = std::complex<double>(array[i].real(), 0);
        }
    }
}

QuantumGate QuantumGate::PauliX{Type::PauliX, 2,
                                {0, 1,
                                 1, 0}};

QuantumGate QuantumGate::PauliY{Type::PauliY, 2,
                                {0, std::complex<double>(0, -1),
                                 std::complex<double>(0, 1), 0}};

QuantumGate QuantumGate::PauliZ{Type::PauliZ, 2,
                                {1, 0,
                                 0, -1}};

QuantumGate QuantumGate::Hadamard2x2{Type::Hadamard, 2,
                                     {1 / std::sqrt(2), 1 / std::sqrt(2),
                                      1 / std::sqrt(2), -1 / std::sqrt(2)}};

QuantumGate QuantumGate::Identity2x2{Type::Identity, 2,
                                     {1, 0,
                                      0, 1}};

QuantumGate QuantumGate::CNOT4x4{Type::CNOT,4,
                                 {1, 0, 0, 0,
                                  0, 1, 0, 0,
                                  0, 0, 0, 1,
                                  0, 0, 1, 0}};

QuantumGate QuantumGate::SWAP4x4{Type::Swap, 4,
                                 {1, 0, 0, 0,
                                  0, 0, 1, 0,
                                  0, 1, 0, 0,
                                  0, 0, 0, 1}};

Statevector operator*(QuantumGate &q, Statevector &v)
{
    if (q.get_cols() != v.size())
    {
        std::cout << "Error: trying to multiply a " << q.get_rows() << "x" << q.get_cols() << " matrix with a " << v.size() << "x1 vector" << std::endl;
        throw("matrix and vector sizes don't match");
    }
    Statevector result(std::log2(q.get_rows()));
    for (size_t i = 0; i < q.get_rows(); i++)
    {
        for (size_t j = 0; j < q.get_cols(); j++)
        {
            result[i] += q(i + 1, j + 1) * v[j];
        }
    }
    return result;
}

/*
 v1 
┌ a1 ┐                      ┌ a1b1 a1b2 . .   a1bn  ┐
| a2 |        v2            | a2b1 a2b2 . .   a2bn  |
| .  | . [b1 b2 . .  bn]  = | .    .    . . .       |
| .  |                      | .    .    . . .       |
└ an ┘                      └ anb1 anb2 . . . anbn  ┘ 

*/
QuantumGate dyad(Statevector &v1, Statevector &v2)
{
    if (v1.size() != v2.size())
    {
        std::cout << "Error: trying to multiply a " << v1.size() << "x1 vector with a " << v2.size() << "x1 vector" << std::endl;
        throw("vector sizes don't match");
    }
    QuantumGate result(v1.size());
    for (size_t i = 0; i < v1.size(); i++)
    {
        for (size_t j = 0; j < v2.size(); j++)
        {
            result(i + 1, j + 1) = v1[i] * v2[j];
        }
    }
    return result;
}

// Identity matrix
QuantumGate Identity(size_t n)
{
    QuantumGate result(n);
    for (size_t i = 0; i < n; i++)
    {
        result(i + 1, i + 1) = 1;
    }

    return result;
}

// Zero matrix
QuantumGate Zeros(size_t n)
{
    QuantumGate result(pow(2, n));
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            result(i + 1, j + 1) = 0;
        }
    }

    return result;
}

std::ostream& operator<<(std::ostream& os, const QuantumGate::Type& type)
{
    switch (type)
    {
        case QuantumGate::Type::Hadamard:
            os << "Hadamard";
            break;
        case QuantumGate::Type::Swap:
            os << "Swap";
            break;
        case QuantumGate::Type::CNOT:
            os << "CNOT";
            break;
        case QuantumGate::Type::PauliX:
            os << "PauliX";
            break;
        case QuantumGate::Type::PauliY:
            os << "PauliY";
            break;
        case QuantumGate::Type::PauliZ:
            os << "PauliZ";
            break;      
        case QuantumGate::Type::Phase:
            os << "Phase";
            break;
        case QuantumGate::Type::Identity:
            os << "Identity";
            break;
        case QuantumGate::Type::Custom:
            os << "Custom";
            break;
    }

    return os;
}

// End of QuantumGate class implementation
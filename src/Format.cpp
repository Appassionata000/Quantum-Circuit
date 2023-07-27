#include "../include/Format.hpp"

std::string complex_to_str(std::complex<double> &num)
{
    if (num.real() == 0.0 && num.imag() != 0.0)
    {
        if (num.imag() == 1.0)
            return "i";
        else if (num.imag() == -1.0)
            return "-i";
        else
        {
            std::ostringstream oss;
            oss << std::setprecision(3) << num.imag();
            std::string str = oss.str();
            return str + "i";
        }
    }
    else if (num.imag() == 0.0 && num.real() != 0.0)
    {
        std::ostringstream oss;
        oss << std::setprecision(3) << num.real();
        std::string str = oss.str();
        return str;
    }
    else if (num.imag() == 0.0 && num.real() == 0.0)
    {
        return "0";
    }
    else
    {
        std::ostringstream oss1;
        oss1 << std::setprecision(3) << num.real();
        if (num.imag() == 1.0)
        {
            std::string str = oss1.str() + "+i";
            return str;
        }
        else if (num.imag() == -1.0)
        {
            std::string str = oss1.str() + "-i";
            return str;
        }
        else
        {
            std::ostringstream oss2;
            oss2 << std::setprecision(3) << num.imag();
            std::string str = oss1.str() + "+" + oss2.str() + "i";
            return str;
        }
    }
}

std::vector<std::string> split(const std::string &s, const std::string &delimiter)
{
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = s.find(delimiter);
    while (end != std::string::npos)
    {
        tokens.push_back(s.substr(start, end - start));
        start = end + delimiter.length();
        end = s.find(delimiter, start);
    }
    tokens.push_back(s.substr(start));
    return tokens;
}

double read_angle_to_radian()
{
    double angle;
    while (true)
    {
        std::cin >> angle;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a value between 0 and 360: ";
        }
        else
            break;
    }
    return angle * M_PI / 180;
}

size_t validate_option(size_t min_value, size_t max_value)
{
    size_t option;
    while (true)
    {
        std::cin >> option;

        if (std::cin.fail() || option < min_value || option > max_value)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a value between " << min_value << " and " << max_value << ": ";
        }
        else
            break;
    }
    return option;
}

void pause_and_continue()
{
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

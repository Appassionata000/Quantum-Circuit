#ifndef FORMAT_HPP
#define FORMAT_HPP

#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <string>
#include <complex>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <limits>

std::string complex_to_str(std::complex<double> &num);

std::vector<std::string> split(const std::string& s, const std::string& delimiter);

double read_angle_to_radian();

size_t validate_option(size_t min_value, size_t max_value);

void pause_and_continue();

#endif 
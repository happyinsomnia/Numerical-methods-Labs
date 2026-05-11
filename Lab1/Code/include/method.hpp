#pragma once
#include <vector>
#include <grid.hpp>

std::vector<double> FiniteDifference(const std::vector<double> &y);
std::vector<double> DividedDifference(const Grid& grid);
std::vector<double> NewtonFrontwardInterpolation(const Grid &grid, const std::vector<double> &x);
std::vector<double> NewtonDividedInterpolation(const Grid &grid, const std::vector<double> &x);
long long Factorial(int n);
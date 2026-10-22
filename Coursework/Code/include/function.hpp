#pragma once
#include <vector>
#include <functional>

double exactSolution(double x);

std::vector<double> buildExactSolution(double a, double b, double h, std::function<double(double)> func);
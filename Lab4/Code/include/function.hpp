#pragma once
#include <functional>
#include <vector>

double exactSolution(double x);

std::vector<double> buildExactSolution(double a, double b, double h, std::function<double(double)> func);
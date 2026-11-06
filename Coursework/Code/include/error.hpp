#pragma once

#include <vector>

double globalError(double yActual, double yMethod);
double maxError(const std::vector<double> &exactValues, const std::vector<double> &methodValues);
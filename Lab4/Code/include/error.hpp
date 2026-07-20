#pragma once
#include <vector>

double norm(const std::vector<double> exact, const std::vector<double> yMethod);

double stepError(double y_method, double y_actual);
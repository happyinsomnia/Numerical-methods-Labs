#pragma once
#include <string>
#include <functional>

void WriteData(const std::string &filename,
               double a,
               double b,
               std::function<double(double, double, int, std::function<double(double)>)> method,
               std::function<double(double)> func,
               const double actualValue);
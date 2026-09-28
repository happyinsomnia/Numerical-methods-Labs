#pragma once
#include <string>
#include <grid.hpp>
#include <vector>

void ComputeErrorsForNodes(const std::string &path, const Grid &actualGrid, const Grid &newtonGrid);
double MaxError(const Grid &actualGrid, const Grid &newtonGrid);
void MaxErrorVsKnots(const std::string &pathUniform,
                     const std::string &pathChebeshivsy,
                     double left,
                     double right,
                     const int numberKnots,
                     const std::vector<double> &plotX,
                     std::function<double(double)> func,
                     const Grid &plotGrid);

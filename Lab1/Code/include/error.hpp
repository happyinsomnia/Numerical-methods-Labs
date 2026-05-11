#pragma once
#include <string>
#include <grid.hpp>
#include <vector>

void ComputeErrorsForNodes(const std::string &path, const Grid &actualGrid, const Grid &newtonGrid);
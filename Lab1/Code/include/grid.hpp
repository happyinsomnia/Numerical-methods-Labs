#pragma once
#include <vector>
#include <functional>
#include <optional>

struct Grid
{
    std::vector<double> x;
    std::vector<double> y;
};

std::vector<double> CreateChebeshivsyKnots(double left, double right, int n);
std::vector<double> CreateUniformKnots(double left, double right, int n);
Grid CreateGrid(const std::vector<double> &x, const std::function<double(double)> &func);
std::optional<double> CheckUniformGrid(const Grid& grid);
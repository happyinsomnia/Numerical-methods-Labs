#include <grid.hpp>
#include <cmath>
#include <numbers>

std::vector<double> CreateChebeshivsyKnots(double left, double right, int n)
{
    std::vector<double> data;

    for (size_t i = 0; i < n; i++)
    {
        double xi = (left + right) / 2.0 + (right - left) / 2.0 * cos(std::numbers::pi * (2.0 * i + 1) / (2.0 * n));

        data.push_back(xi);
    }

    return data;
}

std::vector<double> CreateUniformKnots(double left, double right, int n)
{
    std::vector<double> data(n);

    double h = (right - left) / (n - 1);

    for (size_t i = 0; i < n; i++)
    {
        data[i] = left + i * h;
    }

    return data;
}

std::optional<double> CheckUniformGrid(const Grid &grid)
{
    
    if (grid.x.size() < 2)
        return std::nullopt;

    double h = grid.x[1] - grid.x[0];
    const double epsilon = 1e-9;

    for (size_t i = 2; i < grid.x.size(); i++)
    {
        double current = grid.x[i] - grid.x[i - 1];

        if (std::abs(h - current) > epsilon)
            return std::nullopt;
    }

    return h;
}

Grid CreateGrid(const std::vector<double> &x, const std::function<double(double)> &func)
{
    Grid grid;

    grid.x = x;

    for (auto &elem : x)
        grid.y.push_back(func(elem));

    return grid;
}

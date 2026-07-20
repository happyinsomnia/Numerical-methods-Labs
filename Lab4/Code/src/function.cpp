#include <function.hpp>
#include <cmath>
#include <numbers>
#include <vector>
#include <functional>

double exactSolution(double x)
{
    return std::pow(std::numbers::e, x);
}

std::vector<double> buildExactSolution(double a, double b, double h, std::function<double(double)> func)
{
    std::vector<double> exact;

    for (double step = a; step <= b; step += h)
    {
        exact.push_back(func(step));
    }

    return exact;
    
}

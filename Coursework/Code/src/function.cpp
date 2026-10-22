#include <function.hpp>
#include <math.h>

double exactSolution(double x)
{
    return pow(x + 1, 2);
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
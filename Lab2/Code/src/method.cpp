#include "method.hpp"

double TrapezoidalRule(double a, double b, int N, std::function<double(double)> func)
{
    double h = (b - a) / N;
    double sum = (func(a) + func(b)) / 2.0;

    for (size_t k = 1; k < N; k++)
    {
        sum += func(a + k * h);
    }

    return h * sum;
}
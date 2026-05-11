#include <functions.hpp>
#include <cmath>
#include <stdexcept>

double Function1(double x)
{
    if(x < - 1)
        throw std::invalid_argument("function don't exist in this x");

    return x * log(x + 1);
}

double Function2(double x)
{
    return abs(pow(x, 2) - 2 * x - 3);
}
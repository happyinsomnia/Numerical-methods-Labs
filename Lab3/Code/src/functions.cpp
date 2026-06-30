#include <functions.hpp>
#include <cmath>

double function(double x, double y)
{
    return (4 * x + 2 * y) / (2 * x + 1);
}

double exactFunction(double x)
{
    return (2 * x + 1) * log(std::abs(2 * x + 1)) + 1;
} 
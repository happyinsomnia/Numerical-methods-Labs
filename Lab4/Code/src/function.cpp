#include <function.hpp>
#include <cmath>
#include <numbers>
#include <vector>
#include <functional>

double exactSolution(double x)
{
    return std::pow(std::numbers::e, x);
}

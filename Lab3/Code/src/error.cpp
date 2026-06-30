#include <error.hpp>
#include <cmath>
#include <method.hpp>

double rungeRule(
    int s,
    double x_k,
    double y_k,
    double h,
    std::function<double(double, double)> func,
    std::function<double(double, double, double, std::function<double(double, double)>)> method)
{
    double y_big = method(x_k, y_k, 2 * h, func);

    double y_half = method(x_k, y_k, h, func);
    double y_small = method(x_k + h, y_half, h, func);

    return std::abs(y_big - y_small) / (std::pow(2.0, s) - 1);
}

double absoluteError(double exactValue, double methodValue)
{
    return std::abs(exactValue - methodValue);
}

double localError(double yActual, double yMethod)
{
    return std::abs(yActual - yMethod);
}

double globalError(double yActual, double yMethod)
{
    return std::abs(yActual - yMethod);
}

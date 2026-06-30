#include "method.hpp"

double methodEuler(double x_k, double y_k, double h, std::function<double(double, double)> func)
{
    return y_k + h / 2 * func(x_k, y_k);
}

double modifiedEulerMethod(double x_k, double y_k, double h, std::function<double(double, double)> func)
{
    return y_k + h * func(x_k + h / 2,
                          methodEuler(x_k, y_k, h, func));
}

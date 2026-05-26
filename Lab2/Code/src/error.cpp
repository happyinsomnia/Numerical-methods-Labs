#include <error.hpp>
#include <functions.hpp>

double RungeError(double a,
                  double b,
                  int m,
                  int N,
                  std::function<double(double, double, int, std::function<double(double)>)> method,
                  std::function<double(double)> func)
{
    double error = (std::abs(method(a, b, 2 * N, func) - method(a, b, N, func))) / (pow(2, m) - 1);

    return error;
}

double AbsoluteError(double absoluteValue, double calculatedValue)
{
    return std::abs(absoluteValue - calculatedValue);
}


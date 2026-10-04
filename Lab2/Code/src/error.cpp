#include <error.hpp>
#include <functions.hpp>

// double RungeError(double a,
//                   double b,
//                   int m,
//                   int N,
//                   std::function<double(double, double, int, std::function<double(double)>)> method,
//                   std::function<double(double)> func)
// {
//     double approximation = method(a, b, N, func);

//     return RungeError(a, b, m, N, method, func, approximation);
// }

double RungeError(double a,
                  double b,
                  int m,
                  int N,
                  std::function<double(double, double, int, std::function<double(double)>)> method,
                  std::function<double(double)> func,
                  double &approximation)
{
    double refinedApproximation = method(a, b, 2 * N, func);
    double error = std::abs(refinedApproximation - approximation) / (pow(2, m) - 1);
    approximation = refinedApproximation;

    return error;
}

double AbsoluteError(double absoluteValue, double calculatedValue)
{
    return std::abs(absoluteValue - calculatedValue);
}

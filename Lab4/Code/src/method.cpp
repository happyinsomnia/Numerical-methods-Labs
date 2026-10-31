#include "method.hpp"
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <limits>

// for function s
double methodEuler(double x_k, double s_k, double h, std::function<double(double, double)> func)
{
    return s_k + h / 2 * func(x_k, s_k);
}

double modifiedEulerMethod(double x_k, double s_k, double h, std::function<double(double, double)> func)
{
    return s_k + h * func(x_k + h / 2, methodEuler(x_k, s_k, h, func));
}

// for function t
double methodEuler(double x_k, double t_k, double s_k, double h, std::function<double(double, double, double)> func)
{
    return t_k + h / 2 * func(x_k, t_k, s_k);
}

double modifiedEulerMethod(double x_k, double t_k, double s_k, double s_half, double h, std::function<double(double, double, double)> func)
{
    return t_k + h * func(x_k + h / 2, methodEuler(x_k, t_k, s_k, h, func), s_half);
}

double methodEulerBackwards(double x_k, double y_k, double s_k, double t_k, double h, std::function<double(double, double, double)> func)
{
    return y_k - h / 2 * func(y_k, s_k, t_k);
}

double modifiedEulerMethodBackwards(double x_k, double y_k, double s_k, double s_half, double t_k, double t_half, double h, std::function<double(double, double, double)> func)
{
    return y_k - h * func(methodEulerBackwards(x_k, y_k, s_k, t_k, h, func), s_half, t_half);
}

std::vector<double> factorizationMethod(double a,
                                        double b,
                                        double h,
                                        const DifferentialEquation &equations,
                                        const BoundaryConditions &conditions,
                                        const double delta)
{
    if (!std::isfinite(a) || !std::isfinite(b) || !std::isfinite(h) || h <= 0.0 || b <= a)
        throw std::invalid_argument("a and b must define a finite interval, and h must be positive.");

    const double fineStepCountValue = (b - a) / h;
    if (!std::isfinite(fineStepCountValue) ||
        fineStepCountValue >= static_cast<double>(std::numeric_limits<long long>::max()))
        throw std::invalid_argument("The interval is too large for the requested step.");

    const long long roundedFineStepCount = std::llround(fineStepCountValue);
    const double alignmentTolerance = 64.0 * std::numeric_limits<double>::epsilon() *
                                      std::max(1.0, std::abs(fineStepCountValue));
    if (roundedFineStepCount < 4 || roundedFineStepCount % 4 != 0 ||
        std::abs(fineStepCountValue - roundedFineStepCount) > alignmentTolerance)
        throw std::invalid_argument("The interval length must be an integer multiple of 4h.");

    const std::size_t fineStepCount = static_cast<std::size_t>(roundedFineStepCount);
    const std::size_t tStepCount = fineStepCount / 2;
    const std::size_t yStepCount = fineStepCount / 4;

    std::vector<double> sValues(fineStepCount + 1);
    sValues[0] = -(conditions.alpha_0 / conditions.alpha_1);

    for (std::size_t i = 0; i < fineStepCount; ++i)
    {
        const double x = a + i * h;
        sValues[i + 1] = modifiedEulerMethod(x, sValues[i], h, [&equations](double x_k, double s)
                                             { return -pow(s, 2.0) - equations.q(x_k) / equations.p(x_k) * s - equations.r(x_k) / equations.p(x_k); });
    }

    std::vector<double> tValues(tStepCount + 1);
    tValues[0] = conditions.A / conditions.alpha_1;

    for (std::size_t i = 0; i < tStepCount; ++i)
    {
        const std::size_t sIndex = 2 * i;
        const double x = a + sIndex * h;
        tValues[i + 1] = modifiedEulerMethod(x, tValues[i], sValues[sIndex], sValues[sIndex + 1], 2.0 * h,
                                             [&equations](double x_k, double t, double s)
                                             { return equations.f(x_k) / equations.p(x_k) - s * t - (equations.q(x_k) * t) / equations.p(x_k); });
    }

    std::vector<double> yValues(yStepCount + 1);
    yValues[yStepCount] = (conditions.B - conditions.beta_1 * tValues.back()) /
                              (conditions.beta_0 + conditions.beta_1 * sValues.back()) +
                          delta;

    for (std::size_t i = yStepCount; i > 0; --i)
    {
        const std::size_t sEndIndex = 4 * i;
        const std::size_t tEndIndex = 2 * i;
        const double x = a + sEndIndex * h;
        yValues[i - 1] = modifiedEulerMethodBackwards(x, yValues[i], sValues[sEndIndex], sValues[sEndIndex - 2],
                                                      tValues[tEndIndex], tValues[tEndIndex - 1], 4.0 * h,
                                                      [](double y, double s, double t)
                                                      { return s * y + t; });
    }

    return yValues;
}

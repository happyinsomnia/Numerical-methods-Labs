#include "method.hpp"
#include <cmath>
#include <stdexcept>
#include <algorithm>

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
    std::vector<std::pair<double, double>> s_method;
    std::vector<std::pair<double, double>> t_method;
    std::vector<double> y_method;

    // first element is half , second is whole on k step
    s_method.push_back(std::make_pair(0.0, -(conditions.alpha_0 / conditions.alpha_1)));
    t_method.push_back(std::make_pair(0.0, conditions.A / conditions.alpha_1));

    //* s^h and t^h
    for (double x = a; x + h <= b; x += h)
    {
        double s_half = methodEuler(x, s_method.back().second, h, [&equations](double x_k, double s)
                                    { return -pow(s,2.0) - equations.q(x_k) / equations.p(x_k) * s - equations.r(x_k) / equations.p(x_k); });

        double s_k = modifiedEulerMethod(x, s_method.back().second, h, [&equations](double x_k, double s)
                                         { return -pow(s,2.0) - equations.q(x_k) / equations.p(x_k) * s - equations.r(x_k) / equations.p(x_k); });

        double t_half = methodEuler(x, t_method.back().second, s_method.back().second, h, [&equations](double x_k, double t, double s)
                                    { return equations.f(x_k) / equations.p(x_k) - s * t - (equations.q(x_k) * t) / equations.p(x_k); });

        double t_k = modifiedEulerMethod(x, t_method.back().second, s_k, s_half, h, [&equations](double x_k, double t, double s)
                                         { return equations.f(x_k) / equations.p(x_k) - s * t - (equations.q(x_k) * t) / equations.p(x_k); });

        s_method.push_back(std::make_pair(s_half, s_k));
        t_method.push_back(std::make_pair(t_half, t_k));
    }

    if (s_method.size() != t_method.size())
        throw std::logic_error("s_method and t_method must have the same size. ");

    y_method.push_back((conditions.B - conditions.beta_1 * t_method.back().second) / (conditions.beta_0 + conditions.beta_1 * s_method.back().second) + delta);

    auto s_iter = --s_method.end();
    auto t_iter = --t_method.end();

    for (double x = b; x - h >= a && s_iter != --s_method.begin(); x -= h, --s_iter, --t_iter)
    {
        double y = modifiedEulerMethodBackwards(x, y_method.back(), s_iter->second, s_iter->first, t_iter->second, t_iter->first, h, [](double y, double s, double t)
                                                { return s * y + t; });

        y_method.push_back(y);
    }

    std::reverse(y_method.begin(), y_method.end());

    return y_method;
}

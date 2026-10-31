#include <experiment.hpp>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <numbers>
#include <vector>
#include <method.hpp>

int main()
{
    double A = 3;
    double B = std::numbers::e;
    double alpha_0 = 1;
    double alpha_1 = 2;
    double beta_0 = 1;
    double beta_1 = 0;
    double a = 0;
    double b = 1;

    DifferentialEquation equations([](double x)
                                   { return 1.0; },
                                   [](double x)
                                   { return 2 * x; },
                                   [](double x)
                                   { return 1 + std::pow(x, 2); },
                                   [](double x)
                                   { return (std::pow(x, 2) + 2 * x + 2) * std::pow(std::numbers::e, x); });

    BoundaryConditions conditions(alpha_0,
                                  alpha_1, beta_0, beta_1, A, B);

    RunExperiments("../data/plot_data/", a, b, equations, conditions);

    return 0;
}
#include <iostream>
#include <method.hpp>
#include <cmath>
#include <experiment.hpp>

int main()
{
    double A = 1.0;
    double B = 8.0;
    double alpha_0 = -1.0;
    double alpha_1 = 1.0;
    double beta_0 = 1.0;
    double beta_1 = 1.0;
    double a = 0.0;
    double b = 1.0;

    DifferentialEquation equations([](double x)
                                   { return 1.0; }, [](double x)
                                   { return 1 + x; }, [](double x)
                                   { return -2 - x; }, [](double x)
                                   { return -pow(x, 3) - 2 * x * x - x + 2; });

    BoundaryConditions conditions(alpha_0, alpha_1, beta_0, beta_1, A, B);

    RunExperiments("../data/plot_data/", a, b, equations, conditions, 1.0, 2.0);
    return 0;
}
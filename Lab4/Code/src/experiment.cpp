#include <iostream>
#include "experiment.hpp"
#include <function.hpp>
#include <filesystem>
#include <fstream>
#include <format>
#include <error.hpp>

namespace
{
std::vector<double> buildExactValues(double a, double step, std::size_t count)
{
    std::vector<double> exactValues;
    exactValues.reserve(count);

    for (std::size_t i = 0; i < count; ++i)
        exactValues.push_back(exactSolution(a + i * step));

    return exactValues;
}
}

void RunExperiments(const std::string path,
                    double a,
                    double b,
                    const DifferentialEquation &equations,
                    const BoundaryConditions &conditions)
{
    // First graphic numerical y
    std::filesystem::create_directories(path);

    std::string numericalPath = "Numerical_function.txt";
    std::string errorNumericalPath = "Numerical_function_error.txt";

    std::ofstream fileNumerical(path + numericalPath);
    std::ofstream fileNumericalError(path + errorNumericalPath);

    if (!fileNumerical.is_open())
    {
        std::cerr << "Can't open the file " + numericalPath << std::endl;
        return;
    }

    if (!fileNumericalError.is_open())
    {
        std::cerr << "Can't open the file " + errorNumericalPath << std::endl;
        return;
    }

    fileNumerical << "x vs yMethod \n";
    fileNumericalError << "x vs error \n";

    const double h = 0.001;
    auto y_method = factorizationMethod(a, b, h, equations, conditions);
    const auto exact = buildExactValues(a, 4.0 * h, y_method.size());

    for (std::size_t i = 0; i < y_method.size(); ++i)
    {
        const double x = a + i * 4.0 * h;
        fileNumerical << x << ' ' << y_method[i] << '\n';
        fileNumericalError << x << ' ' << stepError(y_method[i], exactSolution(x)) << '\n';
    }

    fileNumerical.close();
    fileNumericalError.close();

    // Second graphic h vs error

    std::string stepErrorPath = "h_vs_error.txt";

    std::ofstream fileStepError(path + stepErrorPath);

    if (!fileStepError.is_open())
    {
        std::cerr << "Can't open the file " + stepErrorPath << std::endl;
        return;
    }

    fileStepError << "h vs error \n";

    for (int N = 4; N < 10000; N *= 2)
    {
        const double step = (b - a) / N;

        y_method = factorizationMethod(a, b, step, equations, conditions);

        auto yActual = buildExactValues(a, 4.0 * step, y_method.size());
        double error = norm(yActual, y_method);

        fileStepError << step << ' ' << error << '\n';
    }

    fileStepError.close();

    // Third graphic delta vs error

    std::string deltaErrorPath = "delta_vs_error.txt";

    std::ofstream fileDeltaError(path + deltaErrorPath);

    if (!fileDeltaError.is_open())
    {
        std::cerr << "Can't open the file " + deltaErrorPath << std::endl;
        return;
    }

    for (double delta = 1e-1; delta >= 1e-11; delta /= 10)
    {
        y_method = factorizationMethod(a, b, h, equations, conditions, delta);

        double error = norm(exact, y_method);

        fileDeltaError << delta << ' ' << error << '\n';
    }

    fileDeltaError.close();

    // Four graphic Actual function

    std::string actualFunctionPath = "actual_function.txt";
    std::ofstream fileActualFunction(path + actualFunctionPath);

    if (!fileActualFunction.is_open())
    {
        std::cerr << "Can't open the file " + actualFunctionPath << std::endl;
        return;
    }

    fileActualFunction << "x vs y \n";
    for (std::size_t i = 0; i < y_method.size(); ++i)
    {
        const double x = a + i * 4.0 * h;
        fileActualFunction << x << ' ' << exactSolution(x) << '\n';
    }

    fileActualFunction.close();
}

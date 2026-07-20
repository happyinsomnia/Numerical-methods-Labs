#include <iostream>
#include "experiment.hpp"
#include <function.hpp>
#include <filesystem>
#include <fstream>
#include <format>
#include <error.hpp>

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

    auto y_method = factorizationMethod(a, b, 0.001, equations, conditions);

    auto beginIter = y_method.begin();

    for (double a = 0; a <= b; a += 0.001, ++beginIter)
    {
        fileNumerical << a << ' ' << *beginIter << '\n';

        fileNumericalError << a << ' ' << stepError(*beginIter, exactSolution(a)) << '\n';
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

    for (int N = 2; N < 10000; N *= 2)
    {
        double h = (b - a) / N;

        y_method = factorizationMethod(a, b, h, equations, conditions);

        auto yActual = buildExactSolution(a, b, h, exactSolution);
        double error = norm(yActual, y_method);

        fileStepError << h << ' ' << error << '\n';
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

    double h = 0.001;

    auto exact = buildExactSolution(a, b, h, exactSolution);

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
    for (double step = a; step <= b; step += 0.001)
    {
        fileActualFunction << step << ' ' << exactSolution(step) << std::endl;
    }

    fileActualFunction.close();
}

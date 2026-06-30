#include <experiments.hpp>
#include <error.hpp>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <format>
#include <cmath>

void RunExperiment(
    std::string path,
    double x0,
    double y0,
    double right,
    std::function<double(double, double)> func,
    std::function<double(double)> exactFunc,
    std::function<double(double, double, double, std::function<double(double, double)>)> method,
    int s)
{
    std::filesystem::create_directories(path);

    // files Name
    const std::string fileNumericalSolution = path + "x_vs_y_numerical.txt";
    const std::string fileNumericalSolutionError = path + "numerical_solution_error.txt";
    const std::string fileStepAndGlobalError = path + "h_vs_global_error.txt";
    const std::string fileStepAndLocalError = path + "h_vs_local_error.txt";
    const std::string fileEpsilonAndGlobalError = path + "epsilon_vs_global_error.txt";
    const std::string fileDeltaAndGlobalError = path + "delta_vs_global_error.txt";

    // Variables
    double _h = 0.0;
    double _y_k = y0;
    double _x_k = x0;

    // Graphic 1 Approximate graphic
    std::ofstream fileSolution(fileNumericalSolution);
    std::ofstream fileSolutionError(fileNumericalSolutionError);

    if (!fileSolution.is_open() || !fileSolutionError.is_open())
    {
        std::cerr << std::format("Can't open the files {0}, {1}", fileNumericalSolution, fileNumericalSolutionError) << '\n';
        return;
    }

    fileSolution << "x vs y_method \n";
    fileSolutionError << "x vs error \n";

    _h = 0.01;

    for (double x_k = x0; x_k + _h <= right; x_k += _h)
    {
        double y_method = method(x_k, _y_k, _h, func);

        fileSolution << x_k << ' ' << y_method << '\n';

        fileSolutionError << x_k << ' ' << globalError(exactFunc(x_k + _h), y_method) << '\n';
        _y_k = y_method;
    }

    fileSolution.close();

    // Graphic 2 global and local error vs h
    std::ofstream fileGlobal(fileStepAndGlobalError);
    std::ofstream fileLocal(fileStepAndLocalError);

    if (!fileGlobal.is_open() || !fileLocal.is_open())
    {
        std::cerr << std::format("Can't open the files {0}, {1}", fileStepAndGlobalError, fileStepAndLocalError) << '\n';
        return;
    }

    fileGlobal << "h vs globalError " << '\n';
    fileLocal << "h vs localError " << '\n';

    for (double h = 0.4; h >= 1e-4; h /= 2.0)
    {
        double y_k = y0;
        double yk_actual = 0.0;
        double maxErrorGlobal = 0.0;
        double maxErrorLocal = 0.0;

        for (double x_k = x0; x_k + h <= right; x_k += h)
        {
            double y_method = method(x_k, y_k, h, func);

            yk_actual = exactFunc(x_k);

            // Need to for the local error (method with actual value y)
            double y_method_actual = method(x_k, yk_actual, h, func);

            double localErrorValue = localError(exactFunc(x_k + h), y_method_actual);
            double globalErrorValue = globalError(exactFunc(x_k + h), y_method);

            if (maxErrorGlobal < globalErrorValue)
                maxErrorGlobal = globalErrorValue;

            if (maxErrorLocal < localErrorValue)
                maxErrorLocal = localErrorValue;

            y_k = y_method;
        }

        fileGlobal << h << ' ' << maxErrorGlobal << '\n';
        fileLocal << h << ' ' << maxErrorLocal << '\n';
    }

    fileGlobal.close();
    fileLocal.close();

    // Graphic 3 epsilon vs global error
    std::ofstream fileEpsilon(fileEpsilonAndGlobalError);

    if (!fileEpsilon.is_open())
    {
        std::cerr << std::format("Can't open the file {0}", fileEpsilonAndGlobalError) << '\n';
        return;
    }

    fileEpsilon << "epsilon vs global error \n";

    _y_k = y0;

    for (double eps = 1e-1; eps > 1e-11; eps /= 10)
    {
        double maxGlobalError = 0.0;
        double h = 0.5;
        _y_k = y0;

        while (rungeRule(s, x0, y0, h, func, method) > eps)
            h /= 2;

        for (double x_k = x0; x_k + h <= right; x_k += h)
        {
            double y_method = method(x_k, _y_k, h, func);

            double error = globalError(exactFunc(x_k + h), y_method);

            if (error > maxGlobalError)
                maxGlobalError = error;

            _y_k = y_method;
        }

        fileEpsilon << eps << ' ' << maxGlobalError << '\n';
    }

    fileEpsilon.close();

    // Graphic 4 Delta vs Global error

    std::ofstream fileDelta(fileDeltaAndGlobalError);

    if (!fileDelta.is_open())
    {
        std::cerr << std::format("Can't open the file {0}", fileDeltaAndGlobalError) << '\n';
        return;
    }

    fileDelta << "delta vs error \n";

    for (double delta = 1e-1; delta > 1e-11; delta /= 10)
    {
        double h = 0.001;
        double maxGlobalError = 0.0;
        _y_k = y0 + delta;

        for (double x_k = x0; x_k + h <= right; x_k += h)
        {
            double y_method = method(x_k, _y_k, h, func);

            double error = globalError(exactFunc(x_k + h), y_method);

            if (error > maxGlobalError)
                maxGlobalError = error;

            _y_k = y_method;
        }
        fileDelta << delta << ' ' << maxGlobalError << '\n';
    }

    fileDelta.close();
}
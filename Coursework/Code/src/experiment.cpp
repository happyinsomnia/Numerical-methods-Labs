#include <iostream>
#include "experiment.hpp"
#include <function.hpp>
#include <filesystem>
#include <fstream>
#include <format>
#include <chrono>
#include <error.hpp>

void RunExperiments(const std::string path,
                    double a,
                    double b,
                    const DifferentialEquation &equations,
                    const BoundaryConditions &conditions,
                    double y1,
                    double y2)
{
    std::filesystem::create_directories(path);

    std::string fileName = "experiment.csv";

    std::ofstream fileExperiment(path + fileName);

    if (!fileExperiment.is_open())
    {
        std::cerr << "Can't create file: " << fileName << " along the path: " << path << std::endl;
        return;
    }

    fileExperiment << "ModifiedMethodEuler: " << std::endl;

    // Graphic 1: x vs y (modifiedMethodEuler):

    fileExperiment << "Graphic 1: x vs y " << std::endl;

    double _h = 0.001;

    auto modifiedResult = modified_method_Euler::solveODYSecondOrderByModifiedEuler(a, b, _h, y1, y2);

    const auto xAt = [a, b](std::size_t index, std::size_t pointCount)
    {
        return pointCount == 1 ? a : a + (b - a) * index / (pointCount - 1);
    };

    double x = a;

    for (const auto &state : modifiedResult)
    {
        fileExperiment << x << ' ' << state.y1 << '\n';
        x += _h;
    }

    fileExperiment << '\n';

    // Graphic 2: x vs error

    fileExperiment << "Graphic 2: x vs error " << std::endl;

    x = a;

    for (const auto &state : modifiedResult)
    {
        fileExperiment << x << ' ' << globalError(exactSolution(x), state.y1) << std::endl;
        x += _h;
    }

    fileExperiment << std::endl;

    // Graphic 3: h vs error

    fileExperiment << "Graphic 3: h vs error " << std::endl;

    for (double h = 0.5; h >= 1e-4; h /= 2.0)
    {
        modifiedResult = modified_method_Euler::solveODYSecondOrderByModifiedEuler(a, b, h, y1, y2);

        std::vector<double> values;
        values.reserve(modifiedResult.size());

        std::transform(modifiedResult.begin(), modifiedResult.end(), std::back_inserter(values), [](const auto &state)
                       { return state.y1; });

        auto exact = buildExactSolution(a, b, h, exactSolution);
        fileExperiment << h << ' ' << maxError(exact, values) << std::endl;
    }

    fileExperiment << std::endl;

    // Graphic 4: time(sec) vs error

    fileExperiment << "Graphic 4: time vs error " << std::endl;

    for (double h = 0.5; h >= 1e-4; h /= 2.0)
    {
        auto start = std::chrono::steady_clock::now();

        modifiedResult = modified_method_Euler::solveODYSecondOrderByModifiedEuler(a, b, h, y1, y2);

        auto end = std::chrono::steady_clock::now();
        double elapsed = std::chrono::duration<double>(end - start).count();

        std::vector<double> values;
        values.reserve(modifiedResult.size());

        std::transform(modifiedResult.begin(), modifiedResult.end(), std::back_inserter(values), [](const auto &state)
                       { return state.y1; });

        auto exact = buildExactSolution(a, b, h, exactSolution);

        fileExperiment << elapsed << ' ' << maxError(exact, values) << std::endl;
    }

    fileExperiment << std::endl;

    // Factorization Method:

    fileExperiment << "FactorizationMethod: " << std::endl;

    // Graphic 1: x vs y (factorization method):

    fileExperiment << "Graphic 1: x vs y " << std::endl;

    const double factorizationStep = _h / 4.0;
    auto factorizationResult = factorization_method::factorizationMethod(a, b, factorizationStep, equations, conditions);
    const std::size_t factorizationPointCount = factorizationResult.size();

    for (std::size_t i = 0; i < factorizationResult.size(); ++i)
    {
        fileExperiment << xAt(i, factorizationResult.size()) << ' ' << factorizationResult[i] << '\n';
    }

    fileExperiment << '\n';

    // Graphic 2: x vs error

    fileExperiment << "Graphic 2: x vs error " << std::endl;

    for (std::size_t i = 0; i < factorizationResult.size(); ++i)
    {
        const double x = xAt(i, factorizationResult.size());
        fileExperiment << x << ' ' << globalError(exactSolution(x), factorizationResult[i]) << std::endl;
    }

    fileExperiment << std::endl;

    // Graphic 3: h vs error

    fileExperiment << "Graphic 3: h vs error " << std::endl;

    for (double h = 0.25; h >= 1e-4; h /= 2.0)
    {
        factorizationResult = factorization_method::factorizationMethod(a, b, h, equations, conditions);

        std::vector<double> exact;
        exact.reserve(factorizationResult.size());
        for (std::size_t i = 0; i < factorizationResult.size(); ++i)
        {
            exact.push_back(exactSolution(xAt(i, factorizationResult.size())));
        }

        fileExperiment << h << ' ' << maxError(exact, factorizationResult) << std::endl;
    }

    fileExperiment << std::endl;

    // Graphic 4: time(sec) vs error

    fileExperiment << "Graphic 4: time vs error " << std::endl;

    for (double h = 0.25; h >= 1e-4; h /= 2.0)
    {
        auto start = std::chrono::steady_clock::now();

        factorizationResult = factorization_method::factorizationMethod(a, b, h, equations, conditions);

        auto end = std::chrono::steady_clock::now();
        double elapsed = std::chrono::duration<double>(end - start).count();

        std::vector<double> exact;
        exact.reserve(factorizationResult.size());
        for (std::size_t i = 0; i < factorizationResult.size(); ++i)
        {
            exact.push_back(exactSolution(xAt(i, factorizationResult.size())));
        }

        fileExperiment << elapsed << ' ' << maxError(exact, factorizationResult) << std::endl;
    }

    fileExperiment << std::endl;

    fileExperiment.close();

    // Exact function:

    std::string fileNameExactFunction = "exact_function.csv";

    std::ofstream fileExactFunction(path + fileNameExactFunction);

    if (!fileExactFunction.is_open())
    {
        std::cerr << "Can't create file: " << fileNameExactFunction << " along the path: " << path << std::endl;
        return;
    }

    fileExactFunction << "x vs y" << std::endl;

    for (std::size_t i = 0; i < factorizationPointCount; ++i)
    {
        const double x = xAt(i, factorizationPointCount);
        fileExactFunction << x << ' ' << exactSolution(x) << std::endl;
    }

    fileExactFunction.close();
}

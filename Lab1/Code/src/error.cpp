#include "error.hpp"
#include <iostream>
#include <functional>
#include <fstream>
#include <method.hpp>
#include <format>

void ComputeErrorsForNodes(const std::string &path, const Grid &actualGrid, const Grid &newtonGrid)
{
    if (actualGrid.x.size() != newtonGrid.x.size() || actualGrid.y.size() != newtonGrid.y.size())
    {
        std::cout << "Can't compare non-equal grid " << std::endl;
        return;
    }
    std::ofstream file(path);

    if (!file.is_open())
    {
        std::cout << "Can't open the file by path: " + path << std::endl;
        return;
    }

    file << "x :   error: " << '\n';

    for (size_t i = 0; i < actualGrid.x.size(); i++)
    {
        double error = std::abs(actualGrid.y[i] - newtonGrid.y[i]);

        file << actualGrid.x[i] << "   " << error << '\n';
    }
}

double MaxError(const Grid &actualGrid, const Grid &newtonGrid)
{
    double maxError = 0.0;
    if (actualGrid.x.size() != newtonGrid.x.size() || actualGrid.y.size() != newtonGrid.y.size())
    {
        std::cout << "Can't compare non-equal grid " << std::endl;
        return -1;
    }

    for (size_t i = 0; i < actualGrid.x.size(); i++)
    {
        double error = std::abs(actualGrid.y[i] - newtonGrid.y[i]);

        if (error > maxError)
            maxError = error;
    }

    return maxError;
}

void MaxErrorVsKnots(const std::string &pathUniform,
                     const std::string &pathChebeshivsy,
                     double left,
                     double right,
                     const int numberKnots,
                     const std::vector<double> &plotX,
                     std::function<double(double)> func,
                     const Grid &plotGrid)
{
    std::ofstream fileUniform(pathUniform);
    std::ofstream fileChebeshivsy(pathChebeshivsy);

    if (!fileUniform.is_open() || !fileChebeshivsy.is_open())
    {
        std::cout << "Can't open files: " + pathUniform + " " + pathChebeshivsy << std::endl;
        return;
    }

    fileUniform << "knotsValue vs maxError " << std::endl;
    fileChebeshivsy << "knotsValue vs maxError " << std::endl;

    std::vector<double> maxErrorUniform;
    std::vector<double> maxErrorChebeshivsy;

    for (size_t knotsValue = 2; knotsValue < numberKnots + 1; knotsValue++)
    {
        Grid newtonGridError;
        Grid ChebeshivsyGridError;

        const auto knots = CreateUniformKnots(left, right, knotsValue);
        const auto chebKnots = CreateChebeshivsyKnots(left, right, knotsValue);

        newtonGridError.x = plotX;
        ChebeshivsyGridError.x = plotX;

        const auto knotUniformGridError = CreateGrid(knots, func);
        const auto knotChebeshivsyGridError = CreateGrid(chebKnots, func);

        newtonGridError.y = NewtonFrontwardInterpolation(knotUniformGridError, plotX);
        ChebeshivsyGridError.y = NewtonDividedInterpolation(knotChebeshivsyGridError, plotX);

        const double newtonMaxError = MaxError(plotGrid, newtonGridError);
        const double chebeshivsyMaxError = MaxError(plotGrid, ChebeshivsyGridError);

        maxErrorUniform.emplace_back(newtonMaxError);
        maxErrorChebeshivsy.emplace_back(chebeshivsyMaxError);
    }

    for (size_t knotsValue = 0; knotsValue < maxErrorUniform.size(); knotsValue++)
    {
        fileUniform << knotsValue + 2 << " " << maxErrorUniform[knotsValue] << std::endl;
        fileChebeshivsy << knotsValue + 2 << " " << maxErrorChebeshivsy[knotsValue] << std::endl;
    }
}

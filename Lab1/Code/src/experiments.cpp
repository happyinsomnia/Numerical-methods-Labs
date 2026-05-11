#include <experiments.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <method.hpp>
#include <functions.hpp>
#include <error.hpp>
#include <iostream>
#include <gridIO.hpp>
#include <filesystem>

void RunSmoothFunctionExperiment(double left, double right, int numberKnots, int numberPoints)
{
    std::filesystem::create_directories("data/smoothFunction/uniform");
    std::filesystem::create_directories("data/smoothFunction/chebeshivsy");

    // files path:
    const std::string fileKnotsUniform = "data/smoothFunction/uniform/knots_uniform.txt";
    const std::string fileKnotsChebeshivsy = "data/smoothFunction/chebeshivsy/knots_chebeshivsy.txt";
    const std::string fileActualFunction = "data/smoothFunction/actual_function.txt";
    const std::string fileNewtonFrontwardValues = "data/smoothFunction/uniform/newton_frontward_values.txt";
    const std::string fileNewtonChebeshivsyValues = "data/smoothFunction/chebeshivsy/newton_chebeshivsy_values.txt";
    const std::string fileErrorUniform = "data/smoothFunction/uniform/newton_uniform_error.txt";
    const std::string fileErrorChebeshivsy = "data/smoothFunction/chebeshivsy/newton_chebeshivsy_error.txt";

    Grid newtonGrid;
    Grid newtonChebeshivsyGrid;

    const auto xKnots = CreateUniformKnots(left, right, numberKnots);
    const auto chebeshivsyKnots = CreateChebeshivsyKnots(left, right, numberKnots);
    const auto plotX = CreateUniformKnots(left, right, numberPoints);

    newtonGrid.x = plotX;
    newtonChebeshivsyGrid.x = plotX;

    const auto knotUniformGrid = CreateGrid(xKnots, Function1);
    const auto knotChebeshivsyGrid = CreateGrid(chebeshivsyKnots, Function1);
    const auto plotGrid = CreateGrid(plotX, Function1);

    // calculating the values:

    newtonGrid.y = NewtonFrontwardInterpolation(knotUniformGrid, plotX);
    newtonChebeshivsyGrid.y = NewtonDividedInterpolation(knotChebeshivsyGrid, plotX);

    // knots Uniform file:
    SaveGrid(fileKnotsUniform, knotUniformGrid);

    // knots Chebeshivsy file:
    SaveGrid(fileKnotsChebeshivsy, knotChebeshivsyGrid);

    // Actual function File:
    SaveGrid(fileActualFunction, plotGrid);

    // NewtonFrontward file:
    SaveGrid(fileNewtonFrontwardValues, newtonGrid);

    // Newton Chebeshivsy values file:
    SaveGrid(fileNewtonChebeshivsyValues, newtonChebeshivsyGrid);

    // Uniform error:
    ComputeErrorsForNodes(fileErrorUniform, plotGrid, newtonGrid);

    // Chebeshivsy error:
    ComputeErrorsForNodes(fileErrorChebeshivsy, plotGrid, newtonChebeshivsyGrid);
}

void RunNonSmoothFunctionExperiment(double left, double right, int numberKnots, int numberPoints)
{
    std::filesystem::create_directories("data/nonSmoothFunction/uniform");
    std::filesystem::create_directories("data/nonSmoothFunction/chebeshivsy");

    // files path:
    const std::string fileKnotsUniform = "data/nonSmoothFunction/uniform/knots_uniform.txt";
    const std::string fileKnotsChebeshivsy = "data/nonSmoothFunction/chebeshivsy/knots_chebeshivsy.txt";
    const std::string fileActualFunction = "data/nonSmoothFunction/actual_function.txt";
    const std::string fileNewtonFrontwardValues = "data/nonSmoothFunction/uniform/newton_frontward_values.txt";
    const std::string fileNewtonChebeshivsyValues = "data/nonSmoothFunction/chebeshivsy/newton_chebeshivsy_values.txt";
    const std::string fileErrorUniform = "data/nonSmoothFunction/uniform/newton_uniform_error.txt";
    const std::string fileErrorChebeshivsy = "data/nonSmoothFunction/chebeshivsy/newton_chebeshivsy_error.txt";

    Grid newtonGrid;
    Grid newtonChebeshivsyGrid;

    const auto xKnots = CreateUniformKnots(left, right, numberKnots);
    const auto chebeshivsyKnots = CreateChebeshivsyKnots(left, right, numberKnots);
    const auto plotX = CreateUniformKnots(left, right, numberPoints);

    newtonGrid.x = plotX;
    newtonChebeshivsyGrid.x = plotX;

    const auto knotUniformGrid = CreateGrid(xKnots, Function2);
    const auto knotChebeshivsyGrid = CreateGrid(chebeshivsyKnots, Function2);
    const auto plotGrid = CreateGrid(plotX, Function2);

    // calculating the values:

    newtonGrid.y = NewtonFrontwardInterpolation(knotUniformGrid, plotX);
    newtonChebeshivsyGrid.y = NewtonDividedInterpolation(knotChebeshivsyGrid, plotX);

    // knots Uniform file:
    SaveGrid(fileKnotsUniform, knotUniformGrid);

    // knots Chebeshivsy file:
    SaveGrid(fileKnotsChebeshivsy, knotChebeshivsyGrid);

    // Actual function File:
    SaveGrid(fileActualFunction, plotGrid);

    // NewtonFrontward file:
    SaveGrid(fileNewtonFrontwardValues, newtonGrid);

    // Newton Chebeshivsy values file:
    SaveGrid(fileNewtonChebeshivsyValues, newtonChebeshivsyGrid);

    // Uniform error:
    ComputeErrorsForNodes(fileErrorUniform, plotGrid, newtonGrid);

    // Chebeshivsy error:
    ComputeErrorsForNodes(fileErrorChebeshivsy, plotGrid, newtonChebeshivsyGrid);
}

#include "error.hpp"
#include <fstream>
#include <iostream>
#include <functional>

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
        std::cout << "Can't open the file by path " + path << std::endl;
        return;
    }

    file << "x :   error: " << '\n';

    for (size_t i = 0; i < actualGrid.x.size(); i++)
    {
        double error = std::abs(actualGrid.y[i] - newtonGrid.y[i]);

        file << actualGrid.x[i] << "   " << error << '\n';
    }
}
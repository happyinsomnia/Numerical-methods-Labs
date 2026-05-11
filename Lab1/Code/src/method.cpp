#include <method.hpp>
#include <stdexcept>

std::vector<double> FiniteDifference(const std::vector<double> &y)
{
    if (y.empty())
        return {};

    std::vector<std::vector<double>> diff(y.size(), std::vector<double>(y.size()));

    for (size_t i = 0; i < y.size(); i++)
        diff[i][0] = y[i];

    for (size_t j = 1; j < y.size(); j++)
    {
        for (size_t i = 0; i < y.size() - j; i++)
        {
            diff[i][j] = diff[i + 1][j - 1] - diff[i][j - 1];
        }
    }

    return diff[0];
}

std::vector<double> DividedDifference(const Grid &grid)
{
    std::vector<std::vector<double>> diff;

    diff.push_back(grid.y);

    for (size_t j = 1; j < grid.y.size(); j++)
    {
        std::vector<double> column;
        for (size_t i = 0; i < grid.y.size() - j; i++)
        {
            double value = (diff[j - 1][i + 1] - diff[j - 1][i]) / (grid.x[i + j] - grid.x[i]);
            column.push_back(value);
        }

        diff.push_back(column);
    }

    std::vector<double> coefficients;

    for (size_t i = 0; i < grid.y.size(); i++)
    {
        coefficients.push_back(diff[i][0]);
    }

    return coefficients;
}

long long Factorial(int n)
{
    long long value = 1;
    for (size_t i = 2; i <= n; i++)
    {
        value *= i;
    }

    return value;
}

std::vector<double> NewtonFrontwardInterpolation(const Grid &grid, const std::vector<double> &x)
{

    std::vector<double> interpolationValue(x.size());
    auto h = CheckUniformGrid(grid);
    if (!h)
        throw std::invalid_argument("NewtonFrontwardInterpolation can't work with nonuniform grid");

    auto diff = FiniteDifference(grid.y);

    for (size_t i = 0; i < x.size(); i++)
    {
        double value = grid.y[0];

        double t = (x[i] - grid.x[0]) / *h;

        double product = 1.0;

        for (size_t j = 1; j < grid.x.size(); j++)
        {
            product *= (t - (j - 1));

            value += diff[j] * product / Factorial(j);
        }

        interpolationValue[i] = value;
    }

    return interpolationValue;
}

std::vector<double> NewtonDividedInterpolation(const Grid &grid, const std::vector<double> &x)
{
    std::vector<double> interpolationValue(x.size());

    auto diff = DividedDifference(grid);

    for (size_t i = 0; i < x.size(); i++)
    {
        double value = diff[0];

        double product = 1.0;

        for (size_t j = 1; j < grid.x.size(); j++)
        {
            product *= (x[i] - grid.x[j-1]);
            value += diff[j] * product;
        }
        interpolationValue[i] = value;
    }
    return interpolationValue;
}

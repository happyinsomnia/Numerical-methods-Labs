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
    if (grid.x.size() != grid.y.size())
        throw std::invalid_argument("DividedDifference requires matching x and y sizes");

    std::vector<double> coefficients = grid.y;

    for (size_t order = 1; order < coefficients.size(); order++)
    {
        for (size_t i = coefficients.size(); i > order; i--)
        {
            const size_t index = i - 1;
            const double denominator = grid.x[index] - grid.x[index - order];
            if (denominator == 0.0)
                throw std::invalid_argument("DividedDifference requires distinct x values");

            coefficients[index] =
                (coefficients[index] - coefficients[index - 1]) / denominator;
        }
    }

    return coefficients;
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
            product *= (t - (j - 1)) / j;

            value += diff[j] * product;
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
            product *= (x[i] - grid.x[j - 1]);
            value += diff[j] * product;
        }
        interpolationValue[i] = value;
    }
    return interpolationValue;
}

#include <error.hpp>
#include <iostream>

double norm(const std::vector<double> &exact, const std::vector<double> &yMethod)
{
    double maxNorm = 0.0;

    for (size_t i = 0; i < exact.size(); i++)
    {
        double steNorm = std::abs(exact[i] - yMethod[i]);

        if (maxNorm < steNorm)
            maxNorm = steNorm;
    }

    return maxNorm;
}

double stepError(double y_method, double y_actual)
{
    return std::abs(y_actual - y_method);
}

double globalError(double yExact, double yMethod)
{
    return std::abs(yExact - yMethod);
}

double maxError(const std::vector<double> &exactValues, const std::vector<double> &methodValues)
{
    if (exactValues.size() != methodValues.size())
    {
        std::cerr << "Function maxError sizes ain't equal" << std::endl;
        return 0.0;
    }

    double _maxError = 0.0;
    for (size_t i = 0; i < exactValues.size(); i++)
    {
        double step = std::abs(exactValues[i] - methodValues[i]);

        if (step > _maxError)
            _maxError = step;
    }

    return _maxError;
}